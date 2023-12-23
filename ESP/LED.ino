#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const char* ssid = "AB7";
const char* password = "07070707";
const char* mqtt_server = "broker.hivemq.com";
const int LED_PIN = 2; // Change to the pin you are using for the LED

bool isBlinking = false; // Variable to track the blinking state
LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27

void blinkLED(int delayTime) {
  digitalWrite(LED_PIN, HIGH);
  delay(delayTime);
  digitalWrite(LED_PIN, LOW);
  delay(delayTime);
}

void setup_wifi() {
  delay(10);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  lcd.setCursor(0, 1);
  lcd.print("IP address: ");
  lcd.print(WiFi.localIP());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Construct the message from the payload
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println(message);

  // Check the received message for LED control
  if (message.equals("LED_ON")) {
    digitalWrite(LED_PIN, LOW);
    isBlinking = false; // Turn off blinking if it was on
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED Status: ON");
  } else if (message.equals("LED_OFF")) {
    digitalWrite(LED_PIN, HIGH);
    isBlinking = false; // Turn off blinking if it was on
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED Status: OFF");
  } else if (message.equals("LED_BLINK")) {
    isBlinking = true; // Start blinking
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED Status: Blinking");
  }
}

void handleBlinking() {
  while (isBlinking) {
    blinkLED(100); // Blink with a 500ms delay
    client.loop(); // Process MQTT messages during blinking
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "esp8266Client";
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("device/status");
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("MQTT Status: Connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("MQTT Status: Reconnecting");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  handleBlinking(); // Handle blinking separately
}
