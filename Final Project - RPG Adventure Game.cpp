// Liana Hockin
// Final Assignment - RPG Adventure Game
// October 28th 2024

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime> // for random enemy spawns
//libraries

struct Item {//initilizate a struct for the item
    std::string name;
    float price;
    int quantity;
    std::string buffDescription;

    Item(std::string n, float p, int q, std::string buff = "")
        : name(n), price(p), quantity(q), buffDescription(buff) {}
};

struct PlayerInfo { // player info
    std::string name;
    std::string birthday;
    std::string favouriteColour;
    std::string favouriteFood;
    std::string favouriteAnimal;
    std::string videoGame;
    std::string favouriteSeason;
    std::string favouritePerson;
};

// Character class
class Character {
public:
    std::string name;
    std::string ancestry;
    std::string className;
    int abilityScores[6];
    int ancestryBonus[6];
    PlayerInfo playerInfo;
    int hitPoints;
    int attack;
    int defense;
    int experience;
    int level;
    float money;
    std::vector<Item> inventory;

    Character() {
        for (int& score : abilityScores) {
            score = 0; // start score at 0
        }
        hitPoints = 20; // Base hit points
        attack = 5; //base attack etc
        defense = 3;
        experience = 0;
        level = 1;
        money = 100.0f;
        inventory.push_back(Item("Elemental Core, Level 1", 10.0f, 1)); // the 2 basic things the player starts off with
        inventory.push_back(Item("Health Potion", 5.0f, 2));

        for (int& score : abilityScores) {
            score = 0; // starting all new characters out at 0 ability scores
        }
        for (int& bonus : ancestryBonus) {
            bonus = 0; // Initialize ancestry bonuses to 0
        }
    }

    void applyAncestryBonus() {
        if (ancestry == "Human") {
            abilityScores[0] += 2; // Strength
            abilityScores[1] += 2; // Dexterity
        }
        else if (ancestry == "Moonshadow Elf") {
            abilityScores[1] += 3; // Dexterity
            abilityScores[5] += 4; // Charisma
        }
        else if (ancestry == "Dragonborn") {
            abilityScores[0] += 6; // Strength
            abilityScores[3] += 3; // Wisdom
        }
        else if (ancestry == "Gnome") {
            abilityScores[0] += 2; // Strength
            abilityScores[1] += 4; // Dexterity
        }
        else if (ancestry == "Shadowblood Human") {
            abilityScores[0] += 1; // Strength
            abilityScores[1] += 2; // Dexterity
        }
        else if (ancestry == "Aetherkin") {
            abilityScores[2] += 5; // Constitution
            abilityScores[1] += 3; // Dexterity
        }
    }

    void levelUp() { // leveling up the player changes their base stats
        level++; // increase level by one when this is called upon
        hitPoints += 5;
        attack += 2;
        defense += 2;
        std::cout << name << " leveled up to level " << level << "!\n";
    }

    void addExperience(int amount) { // expeirence points to level up
        experience += amount; // increase them by a specified amount
        if (experience >= 10) { // if the players experience has surpassed 10, then level them up! 
            levelUp();
            experience = 0; // must reset the expierence after leveling up for easier use
        }
    }

    void printCharacter() { // the cout character traits for the player!
        std::cout << "\nCharacter Traits:\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Ancestry: " << ancestry << "\n";
        std::cout << "Class: " << className << "\n";
        std::cout << "Hit Points: " << hitPoints << "\n";
        std::cout << "Attack: " << attack << "\n";
        std::cout << "Defense: " << defense << "\n";
        std::cout << "Level: " << level << "\n";
        std::cout << "Experience: " << experience << "\n";
        std::cout << "Money: $" << money << "\n";
        std::cout << "Ability Scores:\n";
        std::cout << "Strength: " << abilityScores[0] << "\n";
        std::cout << "Dexterity: " << abilityScores[1] << "\n";
        std::cout << "Constitution: " << abilityScores[2] << "\n";
        std::cout << "Wisdom: " << abilityScores[3] << "\n";
        std::cout << "Intelligence: " << abilityScores[4] << "\n";
        std::cout << "Charisma: " << abilityScores[5] << "\n";

    printPlayerInfo();
    }

    void printPlayerInfo() {
        std::cout << "\nPlayer Information:\n";
        std::cout << "Birthday: " << playerInfo.birthday << "\n";
        std::cout << "Favourite Colour: " << playerInfo.favouriteColour << "\n";
        std::cout << "Favourite Food: " << playerInfo.favouriteFood << "\n";
        std::cout << "Favourite Animal: " << playerInfo.favouriteAnimal << "\n";
        std::cout << "Video Game: " << playerInfo.videoGame << "\n";
        std::cout << "Favourite Season: " << playerInfo.favouriteSeason << "\n";
        std::cout << "Favourite Person: " << playerInfo.favouritePerson << "\n";
    }

    void displayInventory() {
        std::cout << "Inventory:\n"; // the display of the players inventory
        for (const auto& item : inventory) {
            std::cout << item.name << " - Quantity: " << item.quantity << "\n"; // displays the item name and quantity
        }
    }
};

// Enemy class
class Enemy {
public:
    std::string name; // basic info, name, hit points and attack
    int hitPoints;
    int attack;

    Enemy(std::string n, int hp, int att) : name(n), hitPoints(hp), attack(att) {} // just like i did above with character, but for enemy and their attributes

    void takeDamage(int damage) { // in order for the enemy to take damage
        hitPoints -= damage; // subtract the damage from the enemys hit points, so if the enemy has 30 hit points, takes 6 damage they only have 24 hit points left
        if (hitPoints < 0) hitPoints = 0; //in order for the hitpoints to not go below 0, can only be positive
    }
};

// Merchant class
class Merchant {
private:
    std::vector<Item> weapons;
    std::vector<Item> potions;
    std::vector<Item> food;
    std::vector<Item> pets;

public:
    Merchant() {
        weapons.push_back(Item("Elemental Core, Level 2", 100.0f, 1));
        weapons.push_back(Item("Shield", 16.0f, 1));
        weapons.push_back(Item("Mage's Lost Wand", 23.0f, 1));
        weapons.push_back(Item("Ring of Protection", 21.0f, 1));

        potions.push_back(Item("Health Potion", 5.0f, 10));
        potions.push_back(Item("Mana Potion", 6.0f, 5));

        food.push_back(Item("Cooked Chicken", 8.0f, 7));

        pets.push_back(Item("Riley the Black Cat", 100.0f, 1, "Buff: Stealth"));
        pets.push_back(Item("Pumpkin the Orange Cat", 100.0f, 1, "Buff: Luck"));
        pets.push_back(Item("Conor the Black Lab", 100.0f, 1, "Buff: Strength"));
    }

    void talkToMikage(const std::string& playerName) const { //copied from assignment 1
    std::cout << "\nMikage: Greetings, " << playerName << ". I am Mikage, the merchant of these lands. What would you like to know?\n"
        << "1. Tell me about your items.\n"
        << "2. I want to know about you. What's your story?\n"
        << "3. Just browsing.\n";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1:
        displayInventory(); 
        break;
    case 2:
        tellStory();
        askMoreAboutMikage();
        break;
    case 3:
        std::cout << "\nMikage: Very well! Let me know if you need anything, I am always here for you!\n";
        break;
    default:
        std::cout << "\nMikage: I don't understand that. What do you mean, young hero?\n";
    }
}

    void displayMerchantCard() const {
        std::cout << "\nMerchant Name: Prince Mikage \n";
        std::cout << "Merchant Money: $7,000\n";
        std::cout << "Merchant Inventory: White Wind Wand - Quantity: 1 \n";
        std::cout << "Picture of best friend - Quantity: 1 \n";
        std::cout << "Mana Berries - Quantity: 11 \n";
        std::cout << "Mikage House Cegil - Quantity: 1 \n\n";

        std::cout << "\n--- Merchant Facts ---\n";
        std::cout << "Birthday: " "08/12 ""\n";
        std::cout << "Favourite Colour: " "Purple ""\n";
        std::cout << "Favourite Food: " "Octopus Balls ""\n";
        std::cout << "Favourite Animal: " "Chameleon""\n";
        std::cout << "Favourite Video Game: " "Fifa ""\n";
        std::cout << "Favourite Season: " "Summer""\n";
        std::cout << "Favourite Person: " "His best friend""\n";
        std::cout << "-----------------------\n";
    }

    void displayInventory() const { //const = constant! it is unchangeable! 
        std::cout << "Merchant Inventory:\n";

        std::cout << "\nWeapons:\n";
        for (const auto& item : weapons) {
            std::cout << item.name << " - Price: $" << item.price
                << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
        }

        std::cout << "\nPotions:\n";
        for (const auto& item : potions) {
            std::cout << item.name << " - Price: $" << item.price
                << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
        }

        std::cout << "\nFood:\n";
        for (const auto& item : food) {
            std::cout << item.name << " - Price: $" << item.price
                << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
        }

        std::cout << "\nAnimal Inventory:\n";
        for (const auto& animal : pets) {
            std::cout << animal.name << " - Price: $" << animal.price
                << ", Quantity: " << (animal.quantity > 0 ? std::to_string(animal.quantity) : "SOLD OUT")
                << " (" << animal.buffDescription << ")\n";
        }
        std::cout << "\n";
    }

    bool sellItem(const std::string& itemName, int quantity, float& playerMoney, std::vector<Item>& playerInventory) {
        for (auto& item : weapons) {
            if (item.name == itemName) {
                if (item.quantity == 0) {
                    std::cout << item.name << " is SOLD OUT.\n\n";
                    return false;
                }
                if (item.quantity < quantity) {
                    std::cout << "Not enough " << item.name << " in stock.\n\n";
                    return false;
                }

                float totalCost = item.price * quantity;
                if (playerMoney < totalCost) {
                    std::cout << "Not enough money to buy " << quantity << " of " << item.name << ".\n\n";
                    return false;
                }

                item.quantity -= quantity;
                playerMoney -= totalCost;
                std::cout << "Sold " << quantity << " of " << item.name << ".\n\n";

                bool found = false;
                for (auto& playerItem : playerInventory) {
                    if (playerItem.name == item.name) {
                        playerItem.quantity += quantity;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    playerInventory.push_back(Item(item.name, item.price, quantity));
                }
                return true;
            }
        }

        std::cout << itemName << " not found.\n\n";
        return false;
    }
    private:
        void tellStory() const {
            askMoreAboutMikage(); 
        }

        void askMoreAboutMikage() const {
            std::cout << "1. Mikage... please tell me more about your story.\n"
                << "2. Just browsing.\n";

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                fullStory();
                break;
            case 2:
                std::cout << "\nMikage: Very well! Let me know if you need anything.\n";
                break;
            default:
                std::cout << "\nMikage: I don't understand that. What do you mean?\n";
                break;
            }
        }

        void fullStory() const {
            additionalChoices();
        }

        void additionalChoices() const {
            std::cout << "\nWould you like to know more?\n"
                << "1. Tell me more about your best friend, Mikage.\n"
                << "2. I will help you return home.\n"
                << "3. Goodbye.\n";

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                std::cout << "\nMikage: My best friend was the only one who truly cared for me. We shared everything, our hopes and dreams.\n"
                    << "He was brave, always standing by me, and losing him feels like losing a part of myself.\n"
                    << "His laughter could light up my darkest days, and now, without him, there's a void I can't fill.\n"
                    << "I replay our memories, longing for his smile, knowing that everyday I slowly forget what he looks like.\n"; "\n\n";
                break;
            case 2:
                std::cout << "\nMikage : You would actually help me return home? That truly means the world to me. I’ve been slowly losing hope...\n"
                    << "I cannot remember the way back, but with your help, I believe we can uncover the way together. The only problem, is my lack of powers...\n\n";
                break;
            case 3:
                std::cout << "\nMikage: Goodbye.\n";
                break;
            default:
                std::cout << "\nMikage: I don't understand that. What do you mean?\n";
                break;
            }
        }
};

// Town class
class Town { //set up town class just as i did with the others
public:
    Character character;
    Merchant merchant;
    std::string playerName; 

    void visit() {
        std::cout << "Welcome to the Town of Mavi Kilit!\n";
        bool inTown = true;

        while (inTown) { // the "main menu" of the town
            std::cout << "\nWhat would you like to do?\n";
            std::cout << "1. Talk to the Merchant\n";
            std::cout << "2. Rest for the night\n";
            std::cout << "3. Leave Town\n";
            std::cout << "Choose an option: ";
           
            int choice; // always include int choice to store the players cin choice that they input
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                merchant.displayMerchantCard();
                merchant.displayInventory();
                visitMerchant();
                break;
            case 2:
                rest();
                break;
            case 3:
                inTown = false;
                break;
            default:
                std::cout << "Invalid choice. Please choose again.\n";
            }
        }
    }

private:
    void visitMerchant() { // need to repeat same text as above for town class instead of mercant class
        std::cout << "\nReo: Greetings, I am Reo, the merchant of these lands. What would you like to know ? \n" // changed to hide his family name at first to make the merchant more human like, him being scared of being shunned because of his parents!!
            << "\n1. Tell me about your items.\n" 
            << "2. What's your story?\n"
            << "3. Just browsing.\n"; 

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "\nReo: I have many items from health potions to powerful weapons for you to use on your adventure, " << playerName << "!\n";
            buyItem();
            break;
        case 2:
            tellStory(); // tell story is used in town to avoid repeating huge amounts of text
            break;
        case 3:
            std::cout << "\nReo: Very well! Let me know if you need anything, I am always here for you!\n\n";
            break;
        default:
            std::cout << "\nReo: I don't understand that. What do you mean?\n\n";
            break;
        }
    }

    void buyItem() {
        std::string itemName;
        int quantity;

        std::cout << "Enter the name of the item you want to buy (or type 100 to exit): ";
        std::getline(std::cin, itemName);

        if (itemName == "100") {
            std::cout << "Exiting...\n";
            return; // Exit the merchant interaction
        }

        std::cout << "Enter the quantity: ";
        std::cin >> quantity;
        std::cin.ignore();

        if (!merchant.sellItem(itemName, quantity, character.money, character.inventory)) {
            std::cout << "Purchase failed.\n";
        }
    }

    void tellStory() { // tell story
        std::cout << "\nReo: Ah, as a young prince, I once stood against my parents' oppressive rule, unable to bear their tyranny.\n"
            "I escaped the royal life, determined to fight against their evil, but for reasons I still do not fully understand, I lost my powers.\n"
            "So, I have lived as a humble merchant, quietly plotting to thwart their reign.\n"
            "My loving parents kidnapped my best friend, holding him hostage within my very own place of birth.\n"
            "Over the past few months, I have been uncovering the truth behind my lost strength, and I can feel it awakening within me, one day at a time.\n"
            "I know that one day soon, I will reclaim my rightful place on the throne and restore justice to my kingdom.\n\n";
        askMoreAboutMikage();
    }

    void rest() {
        character.hitPoints = 20; // Restore hit points to full
        std::cout << "You have rested for the night and restored your hit points to " << character.hitPoints << ".\n";
    }
    void askMoreAboutMikage() const {
        std::cout << //all options are the same as before, the basic cout line, then the 3 options, then the switch cases on what the mikage will respond with depending on what the player chooses
            "1. \"You sound alot like prince mikage\", you whisper under your breath. Please tell me more about your story.\n" // i want to keep building loops like in real videogames, where the player must choose between options to make realistic dialogue
            << "2. Just browsing.\n";

        int choice; //stores the choice
        std::cin >> choice; //needs cin instead of cout. cin lets the user input their option into the code to be able to run the choice they choose
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "\nMikage: If you really want to hear, here's my full story.\n"
                << "My name is Mikage, Prince Mikage, and from a young age, I possessed supernatural powers that set me apart.\n"
                << "But instead of being celebrated, I was surrounded by people who cared more about my royal status than about me.\n"
                << "My parents saw me as only royal blood to hold their grip on power even after death.\n"
                << "To them, I was just a means to an end, and the so called friends I had were only drawn to me by fear or ambition.\n"
                << "To escape the suffocating weight of their expectations, I found solace in the woods that bordered the castle.\n"
                << "There, I practiced my powers in secret, yearning to harness them fully.\n"
                << "But my parents loathed my abilities, calling them dangerous.\n"
                << "They wanted me to be their perfect heir, and in order for that to happen, I had to control the chaos within me.\n"
                << "One night, everything for once went right.\n"
                << "In a moment of recklessness, I lost control during a training session.\n"
                << "A surge of energy erupted from within me, and I was left injured and unconscious on the forest grass.\n"
                << "When I finally woke up, I found myself bandaged and tended to by a stranger drawing in the dirt.\n"
                << "He was my age, just over 14 years old, but he knew how to medically save someone, cook meals, and make shelter. It made me wonder just how long he has been living alone.\n"
                << "\"Who are you?\" I croaked, confused and suspicious.\n" // learned that \ includes "" ! so it can be used for people saying things within story! 
                << "\"Did you help me for fame? For money? I don’t need your charity.\"\n"
                << "The stranger looked up with a gentle smile, his white, messy hair moving just above his eyes.\n"
                << "\"I don’t even know who you are. I just saw you hurt and wanted to help.\ He spoke. His body spoke nothing but the truth as he went back to staring at the dirt.\n"
                << "That simple honesty struck a chord deep within me.\n"
                << "For the first time, someone cared for me without wanting something in return.\n"
                << "That day I gave him money, as much money as I could spare. He started living in town, and we started hanging out in secret.\n"
                << "We explored the woods, shared stories, and laughed freely. Something I was never allowed to do as a prince.\n"
                << "With their encouragement, I trained harder than ever, feeling a spark of hope.\n"
                << "Maybe I could make a difference.\n"
                << "As my nineteenth birthday approached, the desire for rebellion ignited within me.\n"
                << "I could no longer ignore the suffering of my people.\n"
                << "We made plans to escape the castle and rally others to our cause.\n"
                << "But just as we were about to act, fate intervened.\n"
                << "My bestfriend was kidnapped by my parents, who threatened to kill them if I didn’t return to the castle.\n"
                << "I felt torn apart.\n"
                << "My parents did not care about me; they only wanted to use me and him as pawns.\n"
                << "Desperate to rescue them, I tried confronting my parents that night.\n"
                << "As soon as I came home, they tried killing him. In the heat of the moment, I grew angry, and my powers surged wildly, but instead of harnessing them, they exploded out of control.\n"
                << "I woke up here, teleported away with the use of my powers, unable to use my powers, and unable to speak my bestfriends name.\n"
                << "Ive tried returning home to rescue him, but for some reason I cant remember how to get home.\n"
                << "My powers did something to me, and I dont know how or what. My memories are slowly dissapearing day by day.\n"
                << "Now powerless and alone, I became a merchant, moving through the bustling market with a hollow smile while secretly searching for a way to regain my abilities and rescue them.\n";

            std::cout << "\nWould you like to know more? \n"
                << "1. Tell me more about your best friend, Mikage.\n"
                << "2. I never knew that you fought on our side... I will help you return home.\n" // changed up some dialouge to make it more intense!
                << "3. Goodbye.\n";

            int additionalChoiceMikage; // stores additional choice, this is just like askmoreaboutmikage variable, but its for after mikage tells you his story. this is for deeper conversation, to ask more about his story. This only appears if you follow the certain steps, like asking mikage about his full story.
            std::cin >> additionalChoiceMikage; // input for the additional choice, whatever number the user types in, it spits out the case number! same as before! 
            std::cin.ignore();

            switch (additionalChoiceMikage) {
            case 1: // include more about his bestfriend to make the player build a connection to the NPC
                std::cout << "\nMikage: My best friend was the only one who truly cared for me. We shared everything, our hopes and dreams.\n"
                    << "He was brave, always standing by me, and losing him feels like losing a part of myself.\n"
                    << "His laughter could light up my darkest days, and now, without him, there's a void I can't fill.\n"
                    << "I replay our memories, longing for his smile, knowing that everyday I slowly forget what he looks like.\n"; "\n\n";
                break;

            case 2:
                std::cout << "\nMikage : You would actually help me return home? That truly means the world to me. I’ve been slowly losing hope...\n"
                    << "I cannot remember the way back, but with your help, I believe we can uncover the way together. The only problem, is my lack of powers...\n\n";

                //add an additional conversation to keep it going
                std::cout << "1. I have powers, i can help you return home, and i can help you control them.\n"
                    << "2. Goodbye.\n";

                int playerChoice; //player choice, another variable just like the others, it is included within the additionalchoicemikage so nothing will clash!
                std::cin >> playerChoice; // the usual cin input
                std::cin.ignore();

                switch (playerChoice) { //another switch with another variable, just like all the others above :)
                case 1: // more lore about NPC can help me build a storyline to help with the growing of my code! This will also help me learn new commands that help me build onto different senarios. 
                    std::cout << "\nYou: Mikage, I was born like you. I have secret powers that can help us. My whole journey was to destroy your parents rule, with these powers i have been gifted to by god.\n" //reveal in the story, to keep the players entertained!
                        << "I have the ability to wield and bend elements to my will, slowly learning how to control them to my liking. I promise you, I will help you rescue your bestfriend, regain your powers, and your throne.\n"
                        << "\nMikage: You are the same as I am... Thank you, I could never begin to repay the kindness you have shown me. I will one day see his face again and free my people thanks to you. \n\n";
                    break;

                case 2:
                    std::cout << "\n Goodbye. \n";
                    break;

                default:
                    std::cout << "\nMikage: I don't understand that. What do you mean, young hero?\n";
                    break;
                }
                break; // break again since this is the end of this specific story route! 

            case 3:
                std::cout << "\nMikage: Goodbye.\n\n";
                break;

            default:
                std::cout << "\nMikage: I don't understand that. What do you mean, young hero?\n\n";
                break;
            }
            break; //needs another break since this is the end of case 1

            // these are the basic responses if the player does not want to learn more about mikage! They are structured like the responses from the varaible talkToMikage!
        case 2:
            std::cout << "\nMikage: Very well! Let me know if you need anything.\n\n";
            break;

        default: //like before, an almost else statement, where if all else fails, if the user doesnt put in those options, it spits out this! 
            std::cout << "\nMikage: I don't understand that. What do you mean, young hero?\n\n";
            break;
        }
    }
}; // end of copied assignment 1


// Game class
class Game { // game class to make main easier to type out at the end
public:
    Character character;
    Merchant merchant;
    Town town; // have to initilize the town as well since its a part of the game just as much as character or merchant class
    float playerMoney;

    Game() : playerMoney(100.0f) {
        std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random enemy generation!!!
    }


    void start() {
        std::cout << "\nWelcome to the Land of Mavi Kilit!\n\n";

        std::cout << "In a world where magical powers are shunned,\n"
            << "the main character possesses the rare ability to\n"
            << "bend elements at will, a secret kept hidden from\n"
            << "a society that fears such abilities. The notorious\n"
            << "Mikage royal family sows chaos and mayhem,\n"
            << "slaughtering innocent families and unleashing\n"
            << "monstrous beasts to maintain their twisted version\n"
            << "of peace.\n\n";

        std::cout << "As the player, you must navigate treacherous lands,\n"
            << "battle formidable enemies, and harness your hidden\n"
            << "powers through leveling up. Only then can you rise\n"
            << "against the Mikage tyranny and reclaim justice for\n"
            << "the oppressed.\n\n";

        createCharacter();
        mainMenu();
    }

private:
    void createCharacter() {
        std::cout << "Enter character name (max 10 characters): ";
        std::getline(std::cin, character.name);
        while (!isValidName(character.name)) {
            std::cout << "Invalid name. Please enter a valid name (max 10 characters): ";
            std::getline(std::cin, character.name);
        }

        character.ancestry = getAncestry();
        character.className = getClass();

        std::cout << "Enter Ability Scores: 1-18\n";
        character.abilityScores[0] = getAbilityScore("Strength");
        character.abilityScores[1] = getAbilityScore("Dexterity");
        character.abilityScores[2] = getAbilityScore("Constitution");
        character.abilityScores[3] = getAbilityScore("Wisdom");
        character.abilityScores[4] = getAbilityScore("Intelligence");
        character.abilityScores[5] = getAbilityScore("Charisma");

        std::cout << "Enter your birthday (e.g. MM/DD): ";
        std::getline(std::cin, character.playerInfo.birthday);
        std::cout << "Enter your favourite colour: ";
        std::getline(std::cin, character.playerInfo.favouriteColour);
        std::cout << "Enter your favourite food: ";
        std::getline(std::cin, character.playerInfo.favouriteFood);
        std::cout << "Enter your favourite animal: ";
        std::getline(std::cin, character.playerInfo.favouriteAnimal);
        std::cout << "Enter your favourite video game: ";
        std::getline(std::cin, character.playerInfo.videoGame);
        std::cout << "Enter your favourite season: ";
        std::getline(std::cin, character.playerInfo.favouriteSeason);
        std::cout << "Enter your favourite person: ";
        std::getline(std::cin, character.playerInfo.favouritePerson);

        character.applyAncestryBonus(); // Apply bonuses after character creation
    }

    bool isValidName(const std::string& name) {
        return name.length() <= 10;
    }

    std::string getAncestry() {
        std::vector<std::string> ancestries = { //list out ancestries
            "Human", "Moonshadow Elf", "Dragonborn", "Gnome","Shadowblood Humans", "Aetherkin"
        };
        std::vector<std::string> blurbs = { //created a list called blurbs since its a blurb of text i wrote regarding the ancestrys
             "\n""Good choice! Humans are adaptable and ambitious, known for their versatility." "\nYou gain +2 Strength and +2 Dexterity.\n",

            "\n""Nice pick! Elusive and graceful, Moonshadow Elves are skilled in stealth and magic.""\nYou gain +3 Dexterity and +4 Charisma \n",

            "\n""Nice one, Born of dragon blood, Dragonborn are fierce warriors.""\nYou gain +6 Strength and +3 Wisdom \n",

            "\n""Brilliant choice, Gnomes are amazing inventors and clever tricksters.""\nYou gain +2 Intelligence and +4 Charisma.\n",

            "\n""Nice! These mysterious humans are rumored to possess very ancient powers.""\nYou gain +1 Strength and +2 Dexterity.\n",

            "\n""Poweful! Aetherkin are beings of pure insane amounts of energy, often considered otherworldly.""\nYou gain +5 Constitution and +3 Dexterity.\n"
        };

        std::cout << "Select Ancestry:\n";
        int index = 1;
        for (const auto& ancestry : ancestries) {
            std::cout << index++ << ". " << ancestry << "\n";
        }

        int choice;
        while (true) {
            std::cout << "Enter choice (1-" << ancestries.size() << ") or 100 to exit: ";
            std::cin >> choice;

            if (choice == 100) {
                std::cout << "Exiting...\n";
                exit(0); // Exit the game
            }

            if (choice >= 1 && choice <= ancestries.size()) {
                std::cout << blurbs[choice - 1] << "\n";
                return ancestries[choice - 1];
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    std::string getClass() { // copied from assignment 2
        std::vector<std::string> classes = {
            "Sorcerer", "Paladin", "Rogue", "Bard", "Ranger", "Cleric", "Artificer" // these are the classes the player can choose from, creates a list
        };
        std::vector<std::string> blurbs = { // same as before, another blurb of information to show to the player
            "\n""Harness the raw power of magic as a Sorcerer.""\n",
            "\n""A protector of the innocent, Paladins wield both sword and divine magic.""\n",
           "\n" "Insanely quick and cunning, Rogues excel in stealth and deception.""\n",
            "\n""Bards weave magic through music and stories.""\n",
            "\n""Rangers are skilled trackers and hunters.""\n",
            "\n""Clerics channel the power of their deities to heal.""\n",
            "\n""Artificers blend magic with machinery!""\n"
        };

        std::cout << "Select Class:\n"; // cout for the player to choose their class
        for (size_t i = 0; i < classes.size(); ++i) { // like above, start counting from 0, not one. runs the loop until i is less than the number of classes, and then increases 1 by one to circle through them all
            std::cout << i + 1 << ". " << classes[i] << "\n"; // prints the number and the name of each class! add one since the player should see it start at 1, not 0, but the computer starts at 0
        }

        int choice; // stores the users choice
        while (true) {
            std::cout << "Enter choice (1-" << classes.size() << "): "; // asks the user to input their choice from 1 to the valid class size (7)
            std::cin >> choice; // Get what the user inputs and stores it in choice

            if (choice == 100) { // if the users choice equals 100, then code returns 0. i chose 100 since there is no 100 the user should be typing into the console. numbers also are read instead of numbers easier
                std::cout << "Exiting...\n";
                exit(0);
            }

            if (choice >= 1 && choice <= classes.size()) { // Check if the choice is valid (between 1 and the number of classes, which is 7)
                std::cout << blurbs[choice - 1] << "\n";
                return classes[choice - 1]; // Subtract 1 because lists start at 0
            }
            else {
                std::cout << "Invalid choice. Please try again.\n"; // if invalid, shows this to the user!
            }
        }
    }

    int getAbilityScore(const std::string& ability) { // wanted to switch it up from assignment 2, with instead doing 1-18 instead of having to spare points
        int score;
        std::cout << ability << ": ";
        while (!(std::cin >> score) || score < 1 || score > 18) {
            std::cout << "Invalid score. Please enter a value between 1 and 18: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return score;
    }

    void mainMenu() {
        int choice;
        do {
            std::cout << "\nMain Menu:\n";
            std::cout << "1. Explore\n";
            std::cout << "2. Visit Town\n"; // Changed from visit merchant to visit town
            std::cout << "3. View Character\n";
            std::cout << "4. Exit Game\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) { // then write out choices from main menu
            case 1:
                explore();
                break;
            case 2:
                town.visit();
                break;
            case 3:
                character.printCharacter();
                character.displayInventory();
                break;
            case 4:
                std::cout << "Thank you for playing!\n";
                break;
            default:
                std::cout << "Invalid choice. Please choose again.\n";
            }
        } while (choice != 4);
    }

    void explore() {
        std::cout << "\nYou sought out to regain peace...\n";
        int enemyType = std::rand() % 3; // std::rand() generates a random number; % 3 ensures the result is 0, 1, or 2 which is because there is 3 enemies to choose from!
        Enemy enemy = spawnEnemy(enemyType); // spawn the enemy
        battle(enemy); // then battle the enemy
    }

    Enemy spawnEnemy(int type) { // tried to keep enemies easy 
        if (type == 0) return Enemy("White Prince", 15, 5); // 15 health, 5 attack power and responds to 0. same idea for the rest
        else if (type == 1) return Enemy("Whisper", 15, 5);
        else return Enemy("King Dredge", 14, 6);
    }

    void battle(Enemy& enemy) {
        std::cout << "A " << enemy.name << " appears!\n";
        while (enemy.hitPoints > 0 && character.hitPoints > 0) {
            std::cout << "You attack the " << enemy.name << "!\n";
            enemy.takeDamage(character.attack);
            std::cout << enemy.name << " HP: " << enemy.hitPoints << "\n";

            // Check if the enemy is still alive after the player's attack
            if (enemy.hitPoints > 0) {
                std::cout << enemy.name << " attacks you!\n";
                character.hitPoints -= enemy.attack;
                std::cout << "Your HP: " << character.hitPoints << "\n";
            }
        }

        // If the character's hit points are 0 or less, print defeat message
        if (character.hitPoints <= 0) {
            std::cout << "You have been defeated by the " << enemy.name << "...\n";
        }
        else {
            std::cout << "You defeated the " << enemy.name << "!\n";
            character.addExperience(10);
            std::cout << "You gained 10 experience points!\n"; // level up every battle for fast gain in base stats
        }
    }

    void visitMerchant() {
        merchant.talkToMikage(character.name); // Allow the player to talk to Mikage

        // Display merchant and character inventories
        merchant.displayMerchantCard();
        std::cout << "\n"; 
        character.displayInventory();
        std::cout << "\n"; 
        merchant.displayInventory();
        std::cout << "\n"; 

        // Display the character's current money
        std::cout << "You have: $" << character.money << "\n\n"; // Display character's money

        std::string itemName;
        int quantity;

        std::cout << "Enter the name of the item you want to buy (or type 100 to exit): ";
        std::getline(std::cin, itemName);

        if (itemName == "100") { // 100 to exit like in prior codes
            std::cout << "Exiting...\n";
            return;
        }

        std::cout << "Enter the quantity: ";
        std::cin >> quantity;
        std::cin.ignore();

        if (quantity == 100) {
            std::cout << "Exiting...\n";
            return; // Exit the game
        }

        // Attempt to sell the item
        if (!merchant.sellItem(itemName, quantity, character.money, character.inventory)) {
            std::cout << "Purchase failed.\n";
        }
    }

};


int main() { // made main short and sweet, it just runs the game class
    Game game; // call the instance, just like Merchant merchant; and Character character;
    game.start(); // then start it
    return 0; // always end with return 0
}
// future development, implementing a system where the merchant joins your team and helps fight
