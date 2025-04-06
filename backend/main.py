from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import csv
from pathlib import Path

app = FastAPI()
FILE = Path(__file__).parent / "../cpp/termine.csv"

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"]
)

class Termin(BaseModel):
    datum: str
    uhrzeit: str
    belegtePlaetze: list[str]

def lade_termine():
    termine = []
    if not FILE.exists():
        return termine
    with open(FILE, newline="") as f:
        for zeile in csv.reader(f):
            if len(zeile) >= 2:
                datum, uhrzeit, *personen = zeile
                termine.append(Termin(datum=datum, uhrzeit=uhrzeit, belegtePlaetze=personen))
    return termine

def speichere_termine(termine: list[Termin]):
    with open(FILE, "w", newline="") as f:
        writer = csv.writer(f)
        for t in termine:
            writer.writerow([t.datum, t.uhrzeit] + t.belegtePlaetze)

@app.get("/termine")
def get_termine():
    return lade_termine()

@app.post("/termine")
def add_termin(termin: Termin):
    termine = lade_termine()
    termine.append(termin)
    speichere_termine(termine)
    return {"message": "Termin hinzugefügt"}

@app.post("/eintragen/{index}")
def eintragen(index: int, name: str):
    termine = lade_termine()
    if index >= len(termine):
        raise HTTPException(status_code=404, detail="Termin nicht gefunden")
    if len(termine[index].belegtePlaetze) >= 4:
        raise HTTPException(status_code=400, detail="Termin voll")
    if name in termine[index].belegtePlaetze:
        raise HTTPException(status_code=400, detail="Bereits eingetragen")
    termine[index].belegtePlaetze.append(name)
    speichere_termine(termine)
    return {"message": "Eingetragen"}

@app.post("/austragen/{index}")
def austragen(index: int, name: str):
    termine = lade_termine()
    if index >= len(termine):
        raise HTTPException(status_code=404, detail="Termin nicht gefunden")
    if name not in termine[index].belegtePlaetze:
        raise HTTPException(status_code=400, detail="Nicht eingetragen")
    termine[index].belegtePlaetze.remove(name)
    speichere_termine(termine)
    return {"message": "Austragen erfolgreich"}
