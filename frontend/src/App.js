import React, { useEffect, useState } from "react";

function App() {
  const [termine, setTermine] = useState([]);
  const [neuerTermin, setNeuerTermin] = useState({ datum: "", uhrzeit: "" });
  const [name, setName] = useState("");

  useEffect(() => {
    ladeTermine();
  }, []);

  const ladeTermine = async () => {
    const res = await fetch("http://localhost:8000/termine");
    const data = await res.json();
    setTermine(data);
  };

  const hinzufuegen = async () => {
    const res = await fetch("http://localhost:8000/termine", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ ...neuerTermin, belegtePlaetze: [] }),
    });
    if (res.ok) {
      setNeuerTermin({ datum: "", uhrzeit: "" });
      ladeTermine();
    }
  };

  const eintragen = async (index) => {
    const res = await fetch(`http://localhost:8000/eintragen/${index}?name=${name}`, {
      method: "POST",
    });
    if (res.ok) ladeTermine();
  };

  const austragen = async (index) => {
    const res = await fetch(`http://localhost:8000/austragen/${index}?name=${name}`, {
      method: "POST",
    });
    if (res.ok) ladeTermine();
  };

  return (
    <div style={{ padding: "2rem", fontFamily: "Arial" }}>
      <h1>Terminverwaltung</h1>

      <div>
        <input
          placeholder="Datum (TT.MM.JJJJ)"
          value={neuerTermin.datum}
          onChange={(e) => setNeuerTermin({ ...neuerTermin, datum: e.target.value })}
        />
        <input
          placeholder="Uhrzeit (HH:MM)"
          value={neuerTermin.uhrzeit}
          onChange={(e) => setNeuerTermin({ ...neuerTermin, uhrzeit: e.target.value })}
        />
        <button onClick={hinzufuegen}>Hinzufügen</button>
      </div>

      <div style={{ marginTop: "1rem" }}>
        <input
          placeholder="Dein Name"
          value={name}
          onChange={(e) => setName(e.target.value)}
        />
      </div>

      <ul>
        {termine.map((t, i) => (
          <li key={i}>
            <strong>{t.datum} {t.uhrzeit}</strong> – {t.belegtePlaetze.length}/4 belegt
            <div>Teilnehmer: {t.belegtePlaetze.join(", ") || "Keine"}</div>
            <button onClick={() => eintragen(i)}>Eintragen</button>
            <button onClick={() => austragen(i)}>Austragen</button>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default App;
