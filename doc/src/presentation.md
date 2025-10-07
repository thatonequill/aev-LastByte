# Welcome to `aev.LastByte`

Let’s not waste time here—let’s get to the details right away.

This isn’t meant to tell you everything that will happen (that would spoil the fun), but rather to explain what's going on.

---

## Universe

The universe is set in a futuristic setting and composed of **2.5 worlds**:

-   The `Glasspace`: a digital world where the main story is set.
-   The `Meatspace`: the physical world, shown in the past or as an alternate reality.
-   The `Fractures`: where both worlds merge into a corrupted, glitchy mess.

---

## Factions

Each world comes with its own enemy faction:

-   `Aevum`: the faction in charge of Glasspace—order and unity for the greater good.

    > _We must move as one. Anything going against our flow will be eliminated._

-   `Verdarch`: the faction in charge of Meatspace—nature’s free flow is their only guide.

    > _One must follow nature’s will, for only it knows what’s best for our world._

---

## Elements

Elements like fire or poison exist in this game. They are called **`Signatures`**, and are organized into **`Types`** for structure.
They are as follows:

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

Some factions will have a **natural resistance** to certain Types, with exceptions. Some Signatures may also have enhanced effects depending on the enemy—for example, `Overload` might cause flying drones to crash, dealing massive damage.

---

## Enemies

Enemies are categorized by **Class** and **Role**, and each will have assigned Signatures.
For instance, a `Disruptor` may use `Hex` to weaken the player.

### Enemy Classes

| **Class**  | **Description**                                                 |
| ---------- | --------------------------------------------------------------- |
| `Basic`    | Standard units. Fill encounters and reinforce faction identity. |
| `Elite`    | High-threat, high-reward units. A threat by themselves.         |
| `Miniboss` | Narrative spike or challenge, less complex than full bosses.    |
| `Boss`     | Named, scripted encounters. End major areas.                    |

### Enemy Roles

| **Role**    | **Description**                               |
| ----------- | --------------------------------------------- |
| `Striker`   | Melee-focused, fast, relentless.              |
| `Caster`    | Uses ranged Magical or Digital Signatures.    |
| `Tank`      | Durable, stalls progress. May taunt or guard. |
| `Sniper`    | High-range, high-damage, low defense.         |
| `Support`   | Non-damaging, maintains other enemies.        |
| `Disruptor` | Alters battle flow via status or terrain.     |
| `Summoner`  | Spawns support units or constructs.           |
| `Hybrid`    | Switches styles or fuses behaviors.           |

---

## Player

The player will have stats to level up by earning experience from battles, quests, or puzzles. A tech tree will let the player unlock skills and define their playstyle.

This part isn't as developed yet, as it's not required for the first build :)
So I’m keeping those ideas to myself for now.

---

## Main Mechanics

Expect mechanics like `looting` and `crafting` to acquire gear.
The player will be able to craft armor, shields, and weapons.

There will be an “inventory Tetris” system, paired with **dimensional storage** to stash your loot while on the move.
I enjoy the idea of **limited usable inventory** space, but looting can get annoying—hence the dimensional storage.
It's a **one-way interface**, accessible only at specific, abundant map points.

---

## Map

The map, referred to as **`The Grid`**, will have a set flow (no procedural generation), with **partially random enemy placements**.

It won’t be fully linear—you’ll need to backtrack to key points over time. Your goal is to gather data after all.

The Grid is divided into **Areas (`Shards`)**, and each Shard into **Nodes**.
Nodes are explorable gameplay spaces.
So:

-   `The Grid` = all Shards
-   A `Shard` = a collection of Nodes

---

## Extensions

Because I’m a nerd who likes nerd things, almost everything in the game (okay, maybe not _everything_ everything) will have a **cosmetic file-extension-like name**.

This serves two main purposes:

-   Helps visually distinguish the world and its logic.
-   Gives the player a fast, visual read of what they're interacting with (e.g., `grid.ShardName` vs. `root.ShardName`).

These are optional and can cause visual clutter—so I plan to add a toggle by category.
(They're **on by default** >:3)

Here are the **map-related extensions** for now:

| **Extension** | **Full Word / Root** | **Meaning / Description**                                       |
| ------------- | -------------------- | --------------------------------------------------------------- |
| `echo.`       | Echo                 | Safe zones and main hub nodes                                   |
| `grid.`       | Grid                 | Aevum shard — structured, network-like Glasspace zones          |
| `node.`       | Node                 | Aevum nodes — explorable areas                                  |
| `axi.`        | Axium                | Aevum bosses — powerful core digital entities                   |
| `root.`       | Root                 | Verdarch shard — organic, natural zones                         |
| `mem.`        | Memory               | Verdarch nodes — explorable areas                               |
| `vest.`       | Vestige              | Verdarch bosses — magical, ancient, beastly remnants            |
| `exo.`        | Exosphere            | Optional node — exploratory side zones                          |
| `∆Null_Void.` | Null Void            | Parkour / transition zone — unstable glitchspace between worlds |
| `trans.`      | Transition           | Interlude nodes — bridges between shards                        |
| `frx.`        | Fracture             | Hybrid shard — merged Glasspace/Meatspace zones                 |
| `err.`        | Error                | Secret bosses — corrupted hybrid entities                       |

It might sound complicated at first, but it quickly becomes second nature.
Later on, weapons will use a similar system instead of traditional labels like “sword” or “bow.”

---

## Gameplay

The game will have **4 (well, 3.5)** gameplay phases:

| **Mode**            | **Use Case**     | **Description**                                                                  |
| ------------------- | ---------------- | -------------------------------------------------------------------------------- |
| `Area Exploration`  | Main mode        | Top-down, slightly angled perspective                                            |
| `Turn-Based Combat` | Combat mode      | Classic turn-based battles. Player vs. enemy format.                             |
| `Parkour`           | Platforming mode | Breaks the main loop. Pure movement-focused sections.                            |
| `Combat Parkour`    | Boss fights      | Like Parkour mode but with added combat mechanics. Exclusive to boss encounters. |

---

### If you want to know anything else, feel free to @ me and I’ll update this doc with anything major that’s missing.
