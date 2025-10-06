## 🧩 **Tier**

Describes the **threat tier** of an enemy, how well it will hold up against the player.

| **Class**  | **Description**                                                   |
| ---------- | ----------------------------------------------------------------- |
| `Basic`    | Standard units. Fills encounters and reinforces faction identity. |
| `Elite`    | High-threat, high-reward units. A threat just by themselves.      |
| `Miniboss` | Narrative spike or challenge, less complex than full bosses.      |
| `Boss`     | Named scripted encounter. Ends major areas.                       |

---

## ⚔️ **Role**

Describes **how the enemy fights**, or its tactical archetype.

| **Role**    | **Description**                               |
| ----------- | --------------------------------------------- |
| `Striker`   | Melee-focused, fast, relentless.              |
| `Caster`    | Uses ranged Magical or Digital Signatures.    |
| `Tank`      | Durable, stalls progress. May taunt or guard. |
| `Sniper`    | High-range, high-damage, low defense.         |
| `Support`   | Non-damaging, maintains other enemies.        |
| `Disruptor` | Alters flow of battle via status or terrain.  |
| `Summoner`  | Spawns support units or constructs.           |
| `Hybrid`    | Switches styles or fuses behaviors.           |

---

## 🧠 **AI Profile**

Describes behavioral traits for balance and narrative clarity.

| **Attribute** | **Scale**                          | **Description**                                                        |
| ------------- | ---------------------------------- | ---------------------------------------------------------------------- |
| `Aggression`  | Low / Moderate / Extreme           | How often it initiates or pursues combat.                              |
| `Speed`       | Sluggish / Standarized / Lightning | Governs movement, reaction time, animation pacing.                     |
| `Focus`       | Scatter / Opportunistic / Locked   | Tendency to stay on the player vs. shift priorities.                   |
| `Weakness`    | List of Signature types            | Signatures it takes extra damage or status from (based on Type logic). |

---

## 💥 **Signatures**

| **Signature** | **Status Effect**       |
| ------------- | ----------------------- |
| **Physical**  |                         |
| `Kinetic`     | Delay / Stagger         |
| `Pierce`      | Bleed                   |
| `Friction`    | Burn                    |
| `Poison`      | Toxin / Degeneration    |
| `Rust`        | Armor Shred             |
| **Digital**   |                         |
| `Script`      | Delay                   |
| `Cognitive`   | Panic                   |
| `Overload`    | Heat / Shutdown         |
| `Packetloss`  | Confusion / Inaccuracy  |
| `Loop`        | Chain Damage            |
| **Magical**   |                         |
| `Aetheric`    | Spiritburn              |
| `Spore`       | Rot                     |
| `Verdant`     | Entangle / Regen Denial |
| `Hex`         | Weakness                |
| `Ash`         | Burn + Wither           |
