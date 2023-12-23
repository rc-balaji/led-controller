import React, { useState } from 'react';
import './App.css';

function App() {
  // const [count, setCount] = useState(0);
  const [Status,setStatus] = useState("OFF")

  function handleOn() {
    alert('Device is ON');
    setStatus("ON");
  }

  function handleOff() {
    alert('Device is OFF');
    setStatus("OFF");
  }

  return (
    <div className="app-container">
      <header>
        <h1>Aravind's Controller</h1>
      </header>
      <main>
        <section>
          <h2>Status: {Status === "OFF" ? 'OFF' : 'ON'}</h2>
          <div className="device-buttons">
            <button onClick={handleOn}>Turn On</button>
            <button onClick={handleOff}>Turn Off</button>
          </div>
        </section>
        <section>
          <h2>Additional Information</h2>
          <p>
            Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam in
            felis eu ex aliquam consectetur.
          </p>
        </section>
      </main>
      <footer>
        <p>&copy; 2023 Smart Home Solutions</p>
      </footer>
    </div>
  );
}

export default App;
