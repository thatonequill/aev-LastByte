#include <iostream> // For input/output operations (like printing to console)
#include <string>	// For using std::string
#include <vector>	// Not directly used in the core system here, but useful for lists
#include <map>		// For storing signatures mapped to their details (efficient lookup)
#include <optional> // For 'exception_res' - indicates a value might or might not be present
#include <utility>	// For std::move, which helps with efficient string handling

// --- 1. Define Enums for Combat Types and Signatures ---
// Enums provide a way to define a set of named integer constants.
// Using 'enum class' makes them strongly typed, preventing implicit conversions.

enum class CombatType
{
	None, // Used for no resistance, unassigned type, or generic situations
	Physical,
	Digital,
	Magical,
	Null,
	// Special values for Exception Resistance - makes it clear which *faction* resists
	Faction_Verdarch_Res, // Indicates that the Verdarch faction resists this specific signature
	Faction_Aevum_Res	  // Indicates that the Aevum faction resists this specific signature
};

enum class Signature
{
	None, // Default or unassigned signature
	// Physical Signatures
	Kinetic,
	Pierce,
	Friction,
	Poison,
	Rust,
	// Digital Signatures
	Script,
	Cognitive,
	Overload,
	Packetloss,
	Loop,
	// Magical Signatures
	Aetheric,
	Spore,
	Verdant,
	Hex,
	Ash,
	// Null Signatures
	Break,
	End,
	N404
};

// Helper function to convert CombatType enum to a human-readable string
// Useful for debugging and displaying information
std::string combatTypeToString(CombatType type)
{
	switch (type)
	{
	case CombatType::Physical:
		return "Physical";
	case CombatType::Digital:
		return "Digital";
	case CombatType::Magical:
		return "Magical";
	case CombatType::Null:
		return "Null";
	case CombatType::None:
		return "None";
	case CombatType::Faction_Verdarch_Res:
		return "Verdarch Faction Resistance";
	case CombatType::Faction_Aevum_Res:
		return "Aevum Faction Resistance";
	}
	return "Unknown CombatType :/"; // Should not happen if all cases are covered
}

// Helper function to convert Signature enum to a human-readable string
std::string signatureToString(Signature sig)
{
	switch (sig)
	{
	// Physical
	case Signature::Kinetic:
		return "Physical - Kinetic";
	case Signature::Pierce:
		return "Physical - Pierce";
	case Signature::Friction:
		return "Physical - Friction";
	case Signature::Poison:
		return "Physical - Poison";
	case Signature::Rust:
		return "Physical - Rust";
	// Digital
	case Signature::Script:
		return "Digital - Script";
	case Signature::Cognitive:
		return "Digital - Cognitive";
	case Signature::Overload:
		return "Digital - Overload";
	case Signature::Packetloss:
		return "Digital - Packetloss";
	case Signature::Loop:
		return "Digital - Loop";
	// Magical
	case Signature::Aetheric:
		return "Magical - Aetheric";
	case Signature::Spore:
		return "Magical - Spore";
	case Signature::Verdant:
		return "Magical - Verdant";
	case Signature::Hex:
		return "Magical - Hex";
	case Signature::Ash:
		return "Magical - Ash";
	// Null
	case Signature::Break:
		return "Null - Break";
	case Signature::End:
		return "Null - End";
	case Signature::N404:
		return "Null - 404";

	case Signature::None:
		return "None";
	}
	return "Unknown Signature :/"; // Should not happen
}

// --- 2. Define Status Effect Structure ---
// For now, it's just a name, but you can expand this later with duration, intensity, etc.
struct StatusEffect
{
	std::string name;
	// Example of future expansion:
	// int duration_turns;
	// float potency_modifier;
};

// --- 3. Define Signature Details Structure ---
// This holds all the information for a specific combat signature.
struct SignatureDetails
{
	CombatType type; // The primary combat type (e.g., Physical, Digital)
	std::string description;
	StatusEffect status_effect;
	// std::optional is used because 'Exception RES' is not present for all signatures.
	// When it has a value, it specifies *which Faction Type* has the exception resistance.
	std::optional<CombatType> exception_res;

	// Constructor to easily create SignatureDetails objects
	SignatureDetails(CombatType t, std::string desc, StatusEffect se, std::optional<CombatType> ex_res = std::nullopt)
		: type(t), description(std::move(desc)), status_effect(std::move(se)), exception_res(std::move(ex_res)) {}

	// Helper method to quickly check if a signature is of type Null
	bool isNullSignature() const
	{
		return type == CombatType::Null;
	}
	bool isDigitalSignature() const
	{
		return type == CombatType::Digital;
	}
	bool isPhysicalSignature() const
	{
		return type == CombatType::Physical;
	}
	bool isMagicalSignature() const
	{
		return type == CombatType::Magical;
	}
};

// --- 4. Define Factions ---
// Enums for the different factions in your game.
enum class Faction
{
	None,
	Verdarch,
	Aevum,
	Error
};

// Helper function to check if a faction has a *base* resistance to a primary combat type.
// This implements the "Faction RES" column from your table.
bool doesFactionResistPrimaryType(Faction faction, CombatType type)
{
	switch (faction)
	{
	case Faction::Verdarch:
		return type == CombatType::Digital; // Verdarch RES Digital
	case Faction::Aevum:
		return type == CombatType::Magical; // Aevum RES Magical
	case Faction::Error:
		return type == CombatType::Null;
	case Faction::None:
		return false; // A generic/unassigned faction has no inherent resistance
	}
	return false; // Default: no resistance for other unlisted factions/types
}

// --- 5. Main Combat Signature System Class ---
// This class manages all the combat signatures and provides methods to query them.
class CombatSignatureSystem
{
public:
	// Constructor: Initializes the system by populating all signatures.
	CombatSignatureSystem()
	{
		initializeSignatures();
	}

	// Method to retrieve the details for a specific signature.
	// Returns a pointer to the details, or nullptr if the signature is not found.
	const SignatureDetails *getSignatureDetails(Signature sig) const
	{
		auto it = signatures.find(sig); // Search for the signature in map
		if (it != signatures.end())
		{
			return &(it->second); // Return a pointer to the found details
		}
		return nullptr; // Signature not found
	}

	// Core method: Determines if an attack with a given signature is resisted by a target faction.
	bool isResisted(Signature attack_signature, Faction target_faction) const
	{
		const SignatureDetails *details = getSignatureDetails(attack_signature);
		if (!details)
		{
			std::cerr << "Error: Attempted to check resistance for unknown signature: "
					  << signatureToString(attack_signature) << std::endl;
			return false; // Unknown signature cannot be resisted (or should error)
		}

		// Rule 1: Null signatures ignore ALL resistance ("No RES (Ever*)")
		if (details->isNullSignature())
		{
			return false;
		}

		// Rule 2: Check for specific exception resistance first.
		// This handles cases like Poison (Physical) resisted by Aevum, and Rust (Physical) resisted by Verdarch.
		if (details->exception_res.has_value())
		{
			if (target_faction == Faction::Aevum && details->exception_res.value() == CombatType::Faction_Aevum_Res)
			{
				return true; // Aevum resists this specific signature (e.g., Poison)
			}
			if (target_faction == Faction::Verdarch && details->exception_res.value() == CombatType::Faction_Verdarch_Res)
			{
				return true; // Verdarch resists this specific signature (e.g., Rust)
			}
		}

		// Rule 3: If no specific exception resistance applies, check base faction resistance
		// for the signature's *primary type*.
		// This handles "Verdarch RES Digital" and "Aevum RES Magical" from main table.
		return doesFactionResistPrimaryType(target_faction, details->type);
	}

private:
	std::map<Signature, SignatureDetails> signatures; // This map stores all the combat data

	// Private method to populate the 'signatures' map with all the data from your tables.
	void initializeSignatures()
	{
		// --- Physical Signatures (🟥) ---
		signatures.emplace(Signature::Kinetic, SignatureDetails(CombatType::Physical, "Blunt force. Hammers, fists, brute strikes.", {"Delay / Stagger"}));
		signatures.emplace(Signature::Pierce, SignatureDetails(CombatType::Physical, "Precision strikes. Needles, rapiers, shots.", {"Bleed"}));
		signatures.emplace(Signature::Friction, SignatureDetails(CombatType::Physical, "Heat from rapid movement or impact.", {"Burn"}));
		signatures.emplace(Signature::Poison, SignatureDetails(CombatType::Physical, "Organic venom. Delayed internal damage.", {"Toxin / Degeneration"}, CombatType::Faction_Aevum_Res)); // Aevum resists Poison
		signatures.emplace(Signature::Rust, SignatureDetails(CombatType::Physical, "Oxidation. Weakens gear and body integrity.", {"Armor Shred"}, CombatType::Faction_Verdarch_Res));	   // Verdarch resists Rust

		// --- Digital Signatures (🟦) ---
		signatures.emplace(Signature::Script, SignatureDetails(CombatType::Digital, "Short code bursts. Logic spikes.", {"Delay"}));
		signatures.emplace(Signature::Cognitive, SignatureDetails(CombatType::Digital, "Emotional overwrite. Forces mood logic.", {"Panic"}));
		signatures.emplace(Signature::Overload, SignatureDetails(CombatType::Digital, "Thermal or voltage surges.", {"Heat / Shutdown"}));
		signatures.emplace(Signature::Packetloss, SignatureDetails(CombatType::Digital, "Memory corruption or missing data blocks.", {"Confusion / Inaccuracy"}));
		signatures.emplace(Signature::Loop, SignatureDetails(CombatType::Digital, "Recursive self-damaging cycle.", {"Chain Damage"}));

		// --- Magical Signatures (🟪) ---
		signatures.emplace(Signature::Aetheric, SignatureDetails(CombatType::Magical, "Traditional soulbound force. Pure aether.", {"Spiritburn"}));
		signatures.emplace(Signature::Spore, SignatureDetails(CombatType::Magical, "Infectious fungal bloom.", {"Rot"}));
		signatures.emplace(Signature::Verdant, SignatureDetails(CombatType::Magical, "Growth as weapon. Binding vines, roots.", {"Entangle / Regen Denial"}));
		signatures.emplace(Signature::Hex, SignatureDetails(CombatType::Magical, "Curse logic, soul destabilizers.", {"Weakness"}));
		signatures.emplace(Signature::Ash, SignatureDetails(CombatType::Magical, "Residue of burnt offerings and rituals.", {"Burn + Wither"}));

		// --- Null Signatures (⚫) ---
		signatures.emplace(Signature::Break, SignatureDetails(CombatType::Null, "Hits through all resistance. No logic applied.", {"True Damage"}));
		signatures.emplace(Signature::End, SignatureDetails(CombatType::Null, "Copies the moment of death in advance.", {"Doomed (Delayed Kill)"}));
		signatures.emplace(Signature::N404, SignatureDetails(CombatType::Null, "Doesn't exist. Still happens.", {"Existence Error"}));
	}
};

// --- Heat System Integration Example ---
// The Heat System you mentioned would typically be integrated into your game's
// attack structures and character/enemy classes. Here's a conceptual outline
// to show how it might fit in:

// 1. Attack Structure: Add heat generation to attacks.
struct Attack
{
	Signature signature;
	int base_damage;
	int heat_generated; // Amount of heat this attack adds to the user/weapon
						// ... potentially other attack properties like target, range, animations, etc.
};

// 2. Character/Weapon System: Manage current heat and max heat.
class Character
{
public:
	std::string name;
	int health;
	int current_heat = 0;
	int max_heat = 50;					  // Max heat before the character suffers consequences
	CombatSignatureSystem &combat_system; // Reference to the central combat system

	Character(std::string n, int hp, CombatSignatureSystem &cs)
		: name(std::move(n)), health(hp), combat_system(cs) {}

	// Method for a character to perform an attack
	void performAttack(const Attack &attack, Faction target_faction)
	{
		std::cout << name << " performs a " << signatureToString(attack.signature)
				  << " attack, generating " << attack.heat_generated << " heat." << std::endl;

		current_heat += attack.heat_generated;

		// Apply heat consequences if over the threshold
		if (current_heat >= max_heat)
		{
			std::cout << "❗ " << name << " is overheating! Self-damage or a penalty applied." << std::endl;
			// Example: Inflict self-damage for overheating
			health -= (current_heat - max_heat); // Damage scales with how much over max heat
			current_heat = max_heat / 2;		 // Reduce heat to a manageable level after overheating
			std::cout << name << "'s health is now " << health << "." << std::endl;
		}

		// Determine if the attack is resisted by the target faction
		if (combat_system.isResisted(attack.signature, target_faction))
		{
			std::cout << "    Attack was resisted by the target faction! Damage might be reduced." << std::endl;
			// Your game logic here: reduce damage, apply a different status, etc.
		}
		else
		{
			std::cout << "    Attack was NOT resisted. Full impact!" << std::endl;
			// Your game logic here: apply full damage/effect
		}
	}
};

// --- Main function to demonstrate the C++ implementation ---
// This is your entry point to run the example.
int main()
{
	std::cout << "Initializing Combat Signature System..." << std::endl;
	CombatSignatureSystem css; // Create an instance of our combat system

	// --- Demonstrating Signature Details Retrieval ---
	std::cout << "\n--- Signature Details Examples ---" << std::endl;

	const SignatureDetails *kinetic_details = css.getSignatureDetails(Signature::Kinetic);
	if (kinetic_details)
	{
		std::cout << "Signature: " << signatureToString(Signature::Kinetic)
				  << " | Type: " << combatTypeToString(kinetic_details->type)
				  << " | Desc: " << kinetic_details->description
				  << " | Effect: " << kinetic_details->status_effect.name << std::endl;
	}

	const SignatureDetails *poison_details = css.getSignatureDetails(Signature::Poison);
	if (poison_details)
	{
		std::cout << "Signature: " << signatureToString(Signature::Poison)
				  << " | Type: " << combatTypeToString(poison_details->type)
				  << " | Desc: " << poison_details->description
				  << " | Effect: " << poison_details->status_effect.name;
		if (poison_details->exception_res.has_value())
		{
			std::cout << " | Exception Res: " << combatTypeToString(poison_details->exception_res.value());
		}
		std::cout << std::endl;
	}

	const SignatureDetails *null_break_details = css.getSignatureDetails(Signature::Break);
	if (null_break_details)
	{
		std::cout << "Signature: " << signatureToString(Signature::Break)
				  << " | Type: " << combatTypeToString(null_break_details->type)
				  << " | Desc: " << null_break_details->description
				  << " | Effect: " << null_break_details->status_effect.name << std::endl;
	}

	// --- Demonstrating Resistance Logic ---
	std::cout << "\n--- Resistance Logic Examples ---" << std::endl;

	std::cout << "\n--- Verdarch Faction Tests ---" << std::endl;
	std::cout << "Verdarch resists Digital (Script)? " << (css.isResisted(Signature::Script, Faction::Verdarch) ? "Yes" : "No") << " (Expected: Yes)" << std::endl;
	std::cout << "Verdarch resists Physical (Kinetic)? " << (css.isResisted(Signature::Kinetic, Faction::Verdarch) ? "Yes" : "No") << " (Expected: No)" << std::endl;
	std::cout << "Verdarch resists Rust (Physical with Verdarch exception)? " << (css.isResisted(Signature::Rust, Faction::Verdarch) ? "Yes" : "No") << " (Expected: Yes)" << std::endl;
	std::cout << "Verdarch resists Null (Break)? " << (css.isResisted(Signature::Break, Faction::Verdarch) ? "Yes" : "No") << " (Expected: No)" << std::endl;

	std::cout << "\n--- Aevum Faction Tests ---" << std::endl;
	std::cout << "Aevum resists Magical (Aetheric)? " << (css.isResisted(Signature::Aetheric, Faction::Aevum) ? "Yes" : "No") << " (Expected: Yes)" << std::endl;
	std::cout << "Aevum resists Physical (Kinetic)? " << (css.isResisted(Signature::Kinetic, Faction::Aevum) ? "Yes" : "No") << " (Expected: No)" << std::endl;
	std::cout << "Aevum resists Poison (Physical with Aevum exception)? " << (css.isResisted(Signature::Poison, Faction::Aevum) ? "Yes" : "No") << " (Expected: Yes)" << std::endl;
	std::cout << "Aevum resists Null (Break)? " << (css.isResisted(Signature::Break, Faction::Aevum) ? "Yes" : "No") << " (Expected: No)" << std::endl;

	std::cout << "\n--- Integrating with a basic Character/Attack system (Heat System example) ---" << std::endl;
	Character player("Hero", 100, css); // Create a player character
	Attack light_physical_attack = {Signature::Kinetic, 10, 5};
	Attack heavy_digital_attack = {Signature::Overload, 25, 20};
	Attack super_magic_attack = {Signature::Aetheric, 30, 30};

	player.performAttack(light_physical_attack, Faction::Verdarch); // Not resisted
	player.performAttack(heavy_digital_attack, Faction::Verdarch);	// Resisted (Verdarch resists Digital)
	player.performAttack(light_physical_attack, Faction::Aevum);	// Not resisted
	player.performAttack(super_magic_attack, Faction::Aevum);		// Resisted (Aevum resists Magical), and also triggers overheat!
	player.performAttack(light_physical_attack, Faction::None);		// Not resisted, continues generating heat

	std::cout << "\nFinal heat for " << player.name << ": " << player.current_heat << std::endl;
	std::cout << "Final health for " << player.name << ": " << player.health << std::endl;

	return 0; // Indicate successful program execution
}