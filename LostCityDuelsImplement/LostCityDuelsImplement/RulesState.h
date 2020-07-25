#include "State.h"
class RulesState:public State
{
public:
	RulesState(sf::RenderWindow& window, std::stack <State*>* states);
	void InitializeButtons(sf::Font& font);
	void Draw();
	bool MouseIsOnPrevious();
	bool MouseIsOnNext();
	//bool MouseIsOnBack();
	void MoveRulePagesForward();
	void MoveRulePagesBackward();
	void Render(sf::RenderTarget& target) override;
	void UpdateEvents(sf::Event& event) override;

private:
	Button m_backButtonText;
	Button m_nextButton;
	Button m_previousButton;
	std::vector<sf::Texture> m_background;
	sf::RectangleShape backgroundShape;
	sf::Font m_font;
	uint16_t m_currentPage=0;
};

