#include "state.hpp"


class ScoreState : public State{
private:
	//SF stuff
	sf::Font font;
	sf::Font titleFont;
	sf::Font scoreFont;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Text title;

	std::vector< sf::Text > scoreTexts;

	//buttons
	Button* exit;

	//else
	int counter;

	//Private functions
	void initFonts();
	void initBackground();
	void initButtons();
	void initScoreTexts();
	void initTitle();
public:
	ScoreState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~ScoreState();

	//Functions
	void updateButtons();
	void updateInput();
	void update();
	void renderScores(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};
