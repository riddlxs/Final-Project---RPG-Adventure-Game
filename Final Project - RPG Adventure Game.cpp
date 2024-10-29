// Liana Hockin
// Final Assignment - RPG Adventure Game
// October 28th 2024

#include <iostream>
#include <string>
#include <vector>
#include <limits>
//libraries

struct Item { // initilizate a struct for the item
    std::string name;
    float price;
    int quantity;
    std::string buffDescription;

    Item(std::string n, float p, int q, std::string buff = "") // buffs onto everything, the name, price , quantity.
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

class Character { // character class
public: // public (can be accessed everywhere in the code)
    std::string name;
    std::string ancestry;
    std::string className;
    int abilityScores[6];
    int hitPoints;
    int attack;
    int defense;
    int experience;
    int level;
    std::vector<Item> inventory;

    Character() {
        for (int& score : abilityScores) {
            score = 0; // start score at 0
        }
        hitPoints = 20; // the base points and level 
        attack = 5;
        defense = 3;
        experience = 0;
        level = 1;
        inventory.push_back(Item("Basic Sword", 10.0f, 1)); // the base inventory for the player
        inventory.push_back(Item("Health Potion", 5.0f, 2));
    }

    void levelUp() { // level up mechanisim
        level++; // increase level by one when this is called upon
        hitPoints += 5;
        attack += 2;
        defense += 2;
        std::cout << name << " leveled up to level " << level << "!\n"; // the cout for the player to read
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
    }

    void displayInventory() {
        std::cout << "Inventory:\n"; // the display of the players inventory
        for (const auto& item : inventory) {
            std::cout << item.name << " - Quantity: " << item.quantity << "\n"; // displays the item name and quantity
        }
    }
};

// now that the player is established, i need to move onto the enemy class 
class Enemy { // public class that can be changed and accessed throughout the code
public:
    std::string name; // basic info, name, hit points and attack
    int hitPoints;
    int attack;

    Enemy(std::string n, int hp, int att) : name(n), hitPoints(hp), attack(att) {} // constructor just like character one

    void takeDamage(int damage) { // in order for the enemy to take damage
        hitPoints -= damage; // subtract the damage from the enemys hit points, so if the enemy has 30 hit points, takes 6 damage they only have 24 hit points left
        if (hitPoints < 0) hitPoints = 0; //in order for the hitpoints to not go below 0, can only be positive
    }
};

// now that enemy class is initilized, must go onto our final character, the merchant. use from past code, to add onto mikage the merchant

    class Merchant {
    private:
        std::vector<Item> weapons; //must now create 4 new items, they must stay private since it cant be changed from the merchants inventory, where as the players can be changed
        std::vector<Item> potions;
        std::vector<Item> food;
        std::vector<Item> pets;

    public: // public is to be able to be used for all classes! 
        Merchant() {

            //added new specific categories within merchants inventory for easier access
            weapons.push_back(Item("Throwing Knife", 15.0f, 22)); //push_back is better than emplace_back sir says. Push uses the copy
            weapons.push_back(Item("Shield", 16.0f, 1));
            weapons.push_back(Item("Mage's Lost Wand", 23.0f, 1));
            weapons.push_back(Item("Ring of Protection", 21.0f, 1));

            potions.push_back(Item("Health Potion", 5.0f, 10));
            potions.push_back(Item("Mana Potion", 6.0f, 5));

            food.push_back(Item("Cooked Chicken", 8.0f, 7));

            pets.push_back(Item("Riley the Black Cat", 100.0f, 1, "Buff: Stealth"));
            pets.push_back(Item("Pumpkin the Orange Cat", 100.0f, 1, "Buff: Luck")); // these buffs do nothing, theyre just for show
            pets.push_back(Item("Conor the Black Lab", 100.0f, 1, "Buff: Strength"));
        }

        void displayMerchantCard() const { //we must include the merchants player card in their class so the user can call upon it in main
            std::cout << "\nMerchant Name: Prince Mikage \n"; //unlike the players card, the merchant has all preset responses on his card since he is an NPC. the player has cin responses for their card
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

            // Display weapons! (i will be doing the same thing for all categories just with the different names!)
            std::cout << "\nWeapons:\n";
            for (const auto& item : weapons) { //auto makes it easier to cycle through the items !!!
                std::cout << item.name << " - Price: $" << item.price
                    << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
            }

            // Display potions!
            std::cout << "\nPotions:\n";
            for (const auto& item : potions) {
                std::cout << item.name << " - Price: $" << item.price
                    << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
            }

            // Display food!
            std::cout << "\nFood:\n";
            for (const auto& item : food) {
                std::cout << item.name << " - Price: $" << item.price
                    << ", Quantity: " << (item.quantity > 0 ? std::to_string(item.quantity) : "SOLD OUT") << "\n";
            }

            // Display pets!
            std::cout << "\nAnimal Inventory:\n";
            for (const auto& animal : pets) {
                std::cout << animal.name << " - Price: $" << animal.price
                    << ", Quantity: " << (animal.quantity > 0 ? std::to_string(animal.quantity) : "SOLD OUT")
                    << " (" << animal.buffDescription << ")\n";
            }
            std::cout << "\n";
        }

        // function to sell the items
        bool sellItem(const std::string& itemName, int quantity, float& playerMoney) {

            // Check weapons inventory (this will all be formatted the same way for the other 3 groups)
            for (auto& item : weapons) {
                if (item.name == itemName) {
                    if (item.quantity == 0) {
                        std::cout << item.name << " is SOLD OUT.\n\n";
                        return false; // item is sold out
                    }
                    if (item.quantity < quantity) {
                        std::cout << "Not enough " << item.name << " in stock.\n\n";
                        return false;// Not enough quantity
                    }
                    float totalCost = item.price * quantity;
                    if (playerMoney < totalCost) {
                        std::cout << "Not enough money to buy " << quantity << " of " << item.name << ".\n\n";
                        return false; // Not enough money
                    }
                    item.quantity -= quantity;
                    playerMoney -= totalCost;
                    std::cout << "Sold " << quantity << " of " << item.name << ".\n\n";
                    return true; // return true when able to sell the item
                }
            }

            // Check potions inventory
            for (auto& item : potions) {
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
                    return true;
                }
            }

            // Check food inventory
            for (auto& item : food) {
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
                    return true;
                }
            }

            // check animal inventory
            for (auto& animal : pets) {
                if (animal.name == itemName) {
                    if (animal.quantity == 0) {
                        std::cout << animal.name << " is SOLD OUT.\n\n";
                        return false;
                    }
                    if (animal.quantity < quantity) {
                        std::cout << "Not enough " << animal.name << " in stock.\n\n";
                        return false;
                    }
                    float totalCost = animal.price * quantity;
                    if (playerMoney < totalCost) {
                        std::cout << "Not enough money to buy " << quantity << " of " << animal.name << ".\n\n";
                        return false;
                    }
                    animal.quantity -= quantity;
                    playerMoney -= totalCost;
                    std::cout << "Sold " << quantity << " of " << animal.name << ".\n\n";
                    return true;
                }
            }

            std::cout << itemName << " not found.\n\n";
            return false; // Sale failed for some other reason
        }

        // Function to get the price of an item by name
        float getItemPrice(const std::string& itemName) const {
            for (const auto& item : weapons) {
                if (item.name == itemName) {
                    return item.price; // return the price if found for weapons
                }
            }
            for (const auto& item : potions) {
                if (item.name == itemName) {
                    return item.price; // return the price if found for potions
                }
            }
            for (const auto& item : food) {
                if (item.name == itemName) {
                    return item.price; // return the price if found for food
                }
            }
            for (const auto& animal : pets) {
                if (animal.name == itemName) {
                    return animal.price; // return the price if found for animals
                }
            }
            return 0.0f; // return no money if not found
        }

        //Function to buy an item from the player !
        void buyItem(const std::string& itemName, int quantity, float& playerMoney, std::vector<Item>& playerInventory) {
            for (auto& item : playerInventory) {
                if (item.name == itemName) {
                    if (item.quantity < quantity) {
                        std::cout << "Not enough " << item.name << " in your inventory.\n\n";
                        return; //doesnt have enough in the players inventory
                    }
                    float sellPrice = item.price * 0.5f; // its basically saying x by 0.5 which is 50 percent lower when sold back to the merchant, wanted to add this to make it seem more realistic! 
                    playerMoney += sellPrice * quantity; // add the money to the players account
                    item.quantity -= quantity; // deduct the quantity
                    if (item.quantity == 0) { // remove from players inventory if quanity reaches 0!
                        playerInventory.erase(std::remove_if(playerInventory.begin(), playerInventory.end(),
                            [&item](const Item& i) { return i.name == item.name; }),
                            playerInventory.end());
                    }

                    // Check if item exists in merchant's inventory
                    for (auto& merchantItem : weapons) {
                        if (merchantItem.name == itemName) { // == means if its the same thing! 
                            merchantItem.quantity += quantity; // increase the merchants quantity
                            std::cout << "Bought " << quantity << " of " << item.name << " from you.\n\n";
                            return; // if the buying is successful and the player has enough to purchase
                        }
                    }
                    for (auto& merchantItem : potions) {
                        if (merchantItem.name == itemName) {
                            merchantItem.quantity += quantity;
                            std::cout << "Bought " << quantity << " of " << item.name << " from you.\n\n";
                            return;
                        }
                    }
                    for (auto& merchantItem : food) {
                        if (merchantItem.name == itemName) {
                            merchantItem.quantity += quantity;
                            std::cout << "Bought " << quantity << " of " << item.name << " from you.\n\n";
                            return;
                        }
                    }
                    for (auto& merchantItem : pets) {
                        if (merchantItem.name == itemName) {
                            merchantItem.quantity += quantity;
                            std::cout << "Bought " << quantity << " of " << item.name << " from you.\n\n";
                            return;
                        }
                    }
                    weapons.push_back(Item(item.name, sellPrice, quantity));
                    std::cout << "Bought " << quantity << " of " << item.name << " from you.\n\n";
                    return;
                }
            }
            std::cout << itemName << " not found in your inventory.\n\n"; // the item was not found!
        }

    void talkToMikage(const std::string& playerName) const { //for some reason, its not letting me change the playername variable to the playerinfo one i was using because its in talktomikage. im still not sure how to fix this, or why it wont let me change it
        std::cout << "\nMikage: Greetings, " << playerName << " I am Mikage, the merchant of these lands.What would you like to know ? \n" // firts thing it shows the player
            << "\n1. Tell me about your items.\n" //items
            << "2. What's your story?\n" //deep story of mikage merchant
            << "3. Just browsing.\n"; // an 'escape' path back to main 'menu'

        int choice;
        std::cin >> choice; // cin for inserting the players choice
        std::cin.ignore();

        //the players choice between 1, 2 and 3 and then the default answer
        switch (choice) {
        case 1:
            std::cout << "\nMikage: I have many items from health potions to powerful weapons for you to use on your adventure " << playerName << "! \n\n";
            break;
        case 2:
            std::cout << "\nMikage: Ah, as a young prince, I once stood against my parents' oppressive rule, unable to bear their tyranny.\n"
                "I escaped the royal life, determined to fight against their evil, but for reasons I still do not fully understand, I lost my powers.\n"
                "So, I have lived as a humble merchant, quietly plotting to thwart their reign.\n"
                "My loving parents kidnapped my best friend, holding him hostage within my very own place of birth.\n"
                "Over the past few months, I have been uncovering the truth behind my lost strength, and I can feel it awakening within me, one day at a time.\n"
                "I know that one day soon, I will reclaim my rightful place on the throne and restore justice to my kingdom.\n\n";
            askMoreAboutMikage(); //input another loop to let the player continue to ask mikage questions! only require this to be added here since it dives more into his story, and not the other options like what he sells or 'just browsing'
            break;
        case 3:
            std::cout << "\nMikage: Very well! Let me know if you need anything, I am always here for you! \n\n";
            break;
        default:
            std::cout << "\nMikage: I don't understand that. What do you mean, young hero?\n\n";
        }
    }
    void askMoreAboutMikage() const { //need to initialize the askmore feature provided above
        std::cout << //all options are the same as before, the basic cout line, then the 3 options, then the switch cases on what the mikage will respond with depending on what the player chooses
            "1. Mikage... please tell me more about your story.\n" // i want to keep building loops like in real videogames, where the player must choose between options to make realistic dialogue
            << "2. Just browsing.\n";

        int choice; //stores the choice
        std::cin >> choice; //needs cin instead of cout. cin lets the user input their option into the code to be able to run the choice they choose
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "\nMikage: If you really want to hear, here's my full story.\n"
                << "My name is Mikage, and from a young age, I possessed supernatural powers that set me apart.\n"
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
                << "\"Did you help me for fame? For money? I don�t need your charity.\"\n"
                << "The stranger looked up with a gentle smile, his white, messy hair moving just above his eyes.\n"
                << "\"I don�t even know who you are. I just saw you hurt and wanted to help.\ He spoke. His body spoke nothing but the truth as he went back to staring at the dirt.\n"
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
                << "My bestfriend was kidnapped by my parents, who threatened to kill them if I didn�t return to the castle.\n"
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
                << "2. I will help you return home.\n"
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
                std::cout << "\nMikage : You would actually help me return home? That truly means the world to me. I�ve been slowly losing hope...\n"
                    << "I cannot remember the way back, but with your help, I believe we can uncover the way together. The only problem, is my lack of powers...\n\n";

                //add an additional conversation to keep it going
                std::cout << "1. I have powers that can help.\n"
                    << "2. Goodbye.\n";

                int playerChoice; //player choice, another variable just like the others, it is included within the additionalchoicemikage so nothing will clash!
                std::cin >> playerChoice; // the usual cin input
                std::cin.ignore();

                switch (playerChoice) { //another switch with another variable, just like all the others above :)
                case 1: // more lore about NPC can help me build a storyline to help with the growing of my code! This will also help me learn new commands that help me build onto different senarios. 
                    std::cout << "\nYou: Mikage, I was born like you. I have secret powers that can help us. My whole journey was to destroy your parents rule, with these powers i have been gifted to by god.\n" //reveal in the story, to keep the players entertained!
                        << "I have the ability to wield and bend elements to my will, slowly learning how to control them to my liking. I promise you, I will help you rescue your bestfriend, regain your powers, and your throne.\n"
                        << "\nMikage: You are the same as I am... Thank you, I could never begin to repay the kindness you have shown me. \n\n";
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


