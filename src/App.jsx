import React, { useState } from 'react';
import axios from 'axios';
import './App.css';

function App() {
  const [status, setStatus] = useState("OFF");

  function handleOn() {
    axios.post('https://led-server.onrender.com/turnOn')
      .then(response => {
        setStatus("ON");
      })
      .catch(error => {
        console.error('Error turning on the LED:', error);
      });
  }

  function handleOff() {
    axios.post('https://led-server.onrender.com/turnOff')
      .then(response => {
        setStatus("OFF");
      })
      .catch(error => {
        console.error('Error turning off the LED:', error);
      });
  }

  function handleBlink() {
    axios.post('https://led-server.onrender.com/blink')
      .then(response => {
        setStatus("BLINKING");
      })
      .catch(error => {
        console.error('Error blinking the LED:', error);
      });
  }

  return (
    <div className="app-container">
      <header>
        <h1>RC Balaji's Controller</h1>
      </header>
      <main>
        <section>
          <h2>Status: {status}</h2>
          <div className="device-buttons">
            <button onClick={handleOn}>Turn On</button>
            <button onClick={handleOff}>Turn Off</button>
            <button onClick={handleBlink}>Blink</button>
          </div>
        </section>
      </main>
      <footer>
        <p>&copy; 2023 Smart Home Solutions</p>
      </footer>
    </div>
  );
}

export default App;
