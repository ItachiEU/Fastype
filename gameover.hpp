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

	//buttons
	Button* exit;

	//Private functions
	void initFonts();
	void initBackground();
	void initButtons();
	void initScore();
public:
	//Constructors
	GameOver(sf::RenderWindow* window, std::stack<State*>* states, sf::Text Text);
	virtual ~GameOver();

	//Accessors


	//Functions
	void updateButtons();
	void updateInput();
	void update();
	void render(sf::RenderTarget* target);
};