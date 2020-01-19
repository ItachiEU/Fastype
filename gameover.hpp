#include "state.hpp"

class GameOver : public State {
private:
	//sf stuff
	sf::Font font;
	sf::Font overFont;
	sf::Font scoreFont;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Text scoreText;
	sf::Text overText;
	sf::Text announcement;

	//buttons
	Button* exit;

	//else
	Player* player;
	bool highScore;

	//Private functions
	void initFonts();
	void initBackground();
	void initButtons();
	void initScore();
	void initAnnouncement();
public:
	//Constructors
	GameOver(sf::RenderWindow* window, std::stack<State*>* states, sf::Text Text, Player* player);
	virtual ~GameOver();

	//Accessors


	//Functions
	void checkHighscore();
	void updateButtons();
	void updateInput();
	void update();
	void render(sf::RenderTarget* target);
};