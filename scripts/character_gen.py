#!/usr/bin/env python3
"""
Character Sheet Generator for aev.LastByte
Creates a Markdown file for a new character based on structured prompts.
"""

from datetime import datetime
import re

# === CONFIG ===
OUTPUT_DIR = "doc/src/characters"  # Folder where files will be saved
TEMPLATE = """# `{name}`

**Faction:** {faction}  
**Role:** {role}  
**Presence:** {presence}  
**Pronouns:** {pronouns}

---

## Overview

{overview}

---

## Persona

- **Demeanor:** {demeanor}  
- **Motivation:** {motivation}  
- **Influence:** {influence}

---

## Appearance

{appearance}

---

## Trivia

- {trivia1}  
- {trivia2}  
- {trivia3}

---
*Generated on {date}*
"""

def sanitize_filename(name):
    """Allow only letters, numbers, and underscores in filenames."""
    safe = re.sub(r'[^A-Za-z0-9_]+', '_', name)
    return safe.strip('_') or "character"


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
    print("=== aev.LastByte Character Sheet Generator ===")

    # Collect data
    name = prompt_field("Character name:")
    faction = prompt_field("Faction:")
    role = prompt_field("Role:")
    presence = prompt_field("Presence (scope / domain):")
    pronouns = prompt_field("Pronouns:")
    overview = prompt_field("Overview:", multiline=True)
    demeanor = prompt_field("Persona - Demeanor:")
    motivation = prompt_field("Persona - Motivation:")
    influence = prompt_field("Persona - Influence:")
    appearance = prompt_field("Appearance:", multiline=True)
    trivia1 = prompt_field("Trivia 1:")
    trivia2 = prompt_field("Trivia 2:")
    trivia3 = prompt_field("Trivia 3:")

    # Fill template
    content = TEMPLATE.format(
        name=name,
        faction=faction,
        role=role,
        presence=presence,
        pronouns=pronouns,
        overview=overview,
        demeanor=demeanor,
        motivation=motivation,
        influence=influence,
        appearance=appearance,
        trivia1=trivia1,
        trivia2=trivia2,
        trivia3=trivia3,
        date=datetime.now().strftime("%Y-%m-%d"),
    )

    # Save file
    filename = os.path.join(OUTPUT_DIR, f"{sanitize_filename(name)}.md")
    with open(filename, "w", encoding="utf-8") as f:
        f.write(content)

    print(f"\n✅ Character sheet saved to: {filename}\n")

if __name__ == "__main__":
    main()
