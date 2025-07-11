# 🔐 Arc Enigma Series — e2 & e3

> “Obfuscation is a primitive form of control. But when it works, it’s magic.” – Arc

## 📜 Background

As a first-year Computer Science student at the University of Queensland, **Arda "Arc" Akgür** became fascinated with the story of the **German Enigma machine** during a late-night systems lab session. The mechanical encryption devices used by the Nazis — and broken by Alan Turing’s team — inspired him to try building a software version that mimicked the **core idea of fixed-key substitution**.

This led to the birth of **`enigma2.c`** — a small C program implementing a randomized one-time-pad-style substitution cipher. It was raw, primitive, and only supported file-based decoding, but it worked.

Years later, with deeper understanding of system design, encryption practices, and deterministic randomness, Arc reimagined the tool in modern form using **.NET 9**. This second version, **`Enigma3Service.cs`**, brings structure, reversibility, and pluggable encryption keys based on deterministic GUID mapping.

The result is a clean lineage of two educational, deterministic obfuscation tools.

---

## 📁 Files

### `enigma2.c` – Classic C Implementation (2000s)

- 🧠 Written in C during UQ study years
- 🗃️ Uses a hardcoded character set and fixed pseudo-random mapping
- 🔐 Encodes and decodes character-by-character using `rand(seed)`
- 🧾 Two modes: File-based or string-to-code
- 🔢 Keycode input is required for correct mapping

> ⚠️ *Warning:* This is not cryptographic. Use only for learning or light obfuscation.

---

### `Enigma3Service.cs` – Modern .NET Implementation (2020s)

- 💡 Rewritten using deterministic mappings and object-oriented patterns
- 🪪 Uses `Guid` to derive one of 10 consistent encryption tables
- 🔄 Each key index maps a shuffled 94-character set using SHA-256-derived seed
- 📦 Two core methods:
  - `Encrypt(Guid id, string plaintext)`
  - `Decrypt(Guid id, string encryptedText)`

> 💬 Exception-safe and fast. Suitable for ID encoding, local storage obfuscation, license key schemes, etc.

---

## 💡 Design Philosophy

Arc's design choices were guided by:

- ✅ Determinism: Same input → same output
- ✅ Reversibility: Every encoded message can be decoded with the right key
- ✅ Simplicity: Avoid full cryptography libraries unless needed
- ✅ Isolation: Works without external storage or dependencies

---

## 🛠️ Usage Example

### `enigma2.c`


gcc enigma2.c -o enigma2
./enigma2
### Enigma3Service.cs

var enigma = new Enigma3Service();
var guid = Guid.NewGuid();

string enc = enigma.Encrypt(guid, "ArcPower42!");
string dec = enigma.Decrypt(guid, enc);
###🧬 Legacy
This project is not about encryption strength — it’s about learning, evolution, and creative experimentation. From the dim-lit labs of Brisbane to modern C# systems, the Enigma series reflects one mind’s ongoing love of code, systems, and secrets.

### 🖋 Author
Arda “Arc” Akgür
Founder & CTO of Arc Corp
akgur.com | GitHub: Arcnaboo
