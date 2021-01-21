# Serious_Games_Project

Serious Games Project for my Honours year in BSc Computer Games Technology.

This project is to create a simple engine based on the Cherno's engine: Hazel, to create a serious game.
The purpose of this game will be to learn japanese characters (Hiragana, Katakana and Kanji) by putting the player in the shoes of a wizard. He will draw those characters with his wand to throw spells

## Game Design Document
### Look and feel


As said in the previous section, Wizard School is a game very inspired by the universe of Harry Potter, especially Hogwarts. This is in this vision that the backgrounds were chosen, as you can see on the figures below. It is inspired by the movies and the games in term of atmosphere and background story. 

![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/ClassRoomBackground.jpg?raw=true)
![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/DuelRoomBackground.jpg?raw=true)

In term of visual, the game is also inspired by visual novels such as Phoenix Wrights games, because those are games that does not use a lot of graphics and they can be run on any kind of machines. That is why a fixed background with some text and interaction on it were chosen. That is the visual style of visual novels, but Phoenix Wright in particular because it offers something else than just dialogs and choices. The gameplay is different, the player can interact with his mouse to do something else than just choose dialogs. He has to investigate and interact with the game to trigger some special events. That is something that this game is inspiring for the interaction with the Japanese characters and in duels.

![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/PhoenixWright.jpg?raw=true)

### Gameplay

#### Core mechanics


The gameplay of the game is based on drawing characters on screen. This is also the main purpose of the game, because, by reproducing characters on the screen, the player will visualize them, and it will help him to remember them. This is how the game works, the player will have to check a model of a character on the screen and he will have to reproduce, by following this model, the character in question. An example of a model is shown on the figure below.
This will lead to duels. After understanding those models, the player would have to reproduce those characters to fight against wizards. If he cannot reproduce it, he loses life. Otherwise, he will hit the wizard with his spell.

![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/MuKatakanaModel.PNG?raw=true)

#### Progression


There is two points of progression in the game. First, the more the player will learn characters, the easier it will be to win duels against wizard, an example is shown below. By winning those duels, and this is the second point, the player will have to fight against stronger opponents and that is how the difficulty will increase.

![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/Character.png?raw=true)

So, the difficulty will increase when the player wins duels. How it will be more difficult? First the opponent will have more life than the previous one of course. That is why the player will have to reproduce more characters than the previous one to beat his opponent. Also, as there is more characters to reproduce, there will be more characters to learn and more difficult ones. The player will first learn Kanas which are the easiest Japanese characters, but after that there is Kanjis and it exists easy Kanjis to learn and really difficult ones.

This evolution of the difficulty in the game will lead the player to first, familiarise with the game and then face up to challenge. This is a progression that is often used in videogames to motivate the player to surpass himself in order to finish the game. Those games can be ones that are not really hard to finish such as Portal or games that are famous to be hard ones such as Doom Eternal or the Dark Souls series.

### Ultimate Aim


The ultimate aim is a very challenging one because it consists of knowing all the characters that are present in the game. Of course, it will take time before the player will finish the game but to learn a language can take years to be mastered. The main purpose of the game is to slowly learn those Japanese characters in order to master all of them. 

### Level Design


The level Design of the game is very simple. It consists of the game mode. The first one is the Training mode and the second one is the Duel mode.

As his name said, the training mode is a screen where a player can train and learn new characters. This is an essential mode because if a wizard does not train himself, he can’t become better than the other. So, in order to win against his opponents, the player will have to train a lot.

The second mode is a kind of story mode. Once the player is ready to, he can try to fight against a wizard to test his capacities. It is like a test.

The level design is inspired by a classic lesson process. The Training mode represents the lessons where the user will learn new characters and then master them, and the Duel mode is the test. If the player passes the test, he can go learn new characters and advance in his quest.

### Narrative


One day, the main character discovered the existence of a wizard school. A dream has come true, he will be able to become a wizard, but not only a simple one: the best wizard of the world. For this, he will have to learn all the spells as possible for a wizard and he will defeat every opponent that are in front of him. Since that day, the history will be written by him because he will be at the top of the wizard’s world.

### GUI


The GUI of the game is pretty simple and consists of which actions can be made on a screen. For example, on Training mode, the player will have the choice the characters that he wants to train. A little menu that lists the different characters.
On Duel mode the GUI is way more simple because there is no menu. There will be on screen only, the models of the characters, life of the player and of the opponent and messages that will give information to the player.
In order to make this game accessible to everyone, the player will only need his mouse to play and there is only one useful button. The left mouse button is available to select on the menus and to draw.

### Conception


The game will be developed by creating his own game engine. This engine will be inspired by the Hazel engine from The Cherno which is available on Youtube. Using C++ and by following the UML class diagram, the game will be implemented by using few libraries such as OpenGL for graphics, imgui for the GUI, GLFW for the windowing, GLSL for the shaders and stb_image for the texture.

![alt text](https://github.com/simon-gonand/Serious_Games_Project/blob/main/GDD_Resources/UML.png?raw=true)
