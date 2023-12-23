const express = require('express');
const mqtt = require('mqtt');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 3001;

const mqttServer = 'mqtt://broker.hivemq.com';
const mqttClient = mqtt.connect(mqttServer);

mqttClient.on('connect', () => {
  console.log('Connected to MQTT server');
});

mqttClient.on('error', (err) => {
  console.error('Error connecting to MQTT server:', err);
});

app.use(cors());
app.use(express.json());

app.post('/turnOn', (req, res) => {
  mqttClient.publish('device/status', 'LED_ON');
  res.json({ success: true, message: 'LED turned ON' });
});

app.post('/turnOff', (req, res) => {
  mqttClient.publish('device/status', 'LED_OFF');
  res.json({ success: true, message: 'LED turned OFF' });
});

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
