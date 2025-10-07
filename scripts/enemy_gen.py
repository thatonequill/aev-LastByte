#!/usr/bin/env python3
"""
Enemy Sheet Generator for aev.LastByte
Creates Markdown files for enemies with tiers, roles, AI profile, and signatures.
"""

from datetime import datetime
import os
import re

# === CONFIG ===
OUTPUT_DIR = "doc/src/enemies"

TEMPLATE = """# `{name}`

**Faction:** {faction}  
**Zone:** {zone}  
**Class:** {tier}  
**Type:** {type}  
**Signature:** {signature}  

---

**ID:** `{name}`  
**Model / Archetype:** {archetype}  
**Behavior:** {behavior}

---

## AI Profile

- Aggression: {aggression}  
- Speed: {speed}  
- Focus: {focus}  
- Weakness: {weakness}

---

## Flavor / Notes

{flavor}

---

*Generated on {date}*
"""

def sanitize_filename(name):
    """Allow only letters, numbers, and underscores in filenames."""
    safe = re.sub(r'[^A-Za-z0-9_]+', '_', name)
    return safe.strip('_') or "enemy"

def prompt_field(label, multiline=False):
    """Prompt user for input; supports multiline entries."""
    print(f"\n{label}")
    if multiline:
        print("(Enter multiple lines. End with a single '.' on a new line.)")
        lines = []
        while True:
            line = input("> ")
            if line.strip() == ".":
                break
            lines.append(line)
        return "\n".join(lines).strip()
    else:
        return input("> ").strip()

def main():
    print("=== aev.LastByte Enemy Sheet Generator ===")
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Collect info
    name = prompt_field("Enemy name / ID:")
    faction = prompt_field("Faction:")
    zone = prompt_field("Zone / Area:")
    tier = prompt_field("Tier (Basic / Elite / Miniboss / Boss):")
    type_ = prompt_field("Type (Physical / Digital / Magical / Hybrid):")
    signature = prompt_field("Signature / Status Effect (optional):")
    archetype = prompt_field("Model / Archetype:")
    behavior = prompt_field("Behavior / AI description:", multiline=True)

    # AI Profile
    aggression = prompt_field("AI Profile - Aggression (Low / Moderate / Extreme):")
    speed = prompt_field("AI Profile - Speed (Sluggish / Standarized / Lightning):")
    focus = prompt_field("AI Profile - Focus (Scatter / Opportunistic / Locked):")
    weakness = prompt_field("AI Profile - Weakness (comma-separated):")

    flavor = prompt_field("Flavor text / Notes:", multiline=True)

    # Fill template
    content = TEMPLATE.format(
        name=name,
        faction=faction,
        zone=zone,
        tier=tier,
        type=type_,
        signature=signature,
        archetype=archetype,
        behavior=behavior,
        aggression=aggression,
        speed=speed,
        focus=focus,
        weakness=weakness,
        flavor=flavor,
        date=datetime.now().strftime("%Y-%m-%d"),
    )

    # Save file
    filename = os.path.join(OUTPUT_DIR, f"{sanitize_filename(name)}.md")
    with open(filename, "w", encoding="utf-8") as f:
        f.write(content)

    print(f"\n✅ Enemy sheet saved to: {filename}\n")

if __name__ == "__main__":
    main()
