#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include <string>
#include <vector>
#include <map>

using namespace sf;

#ifndef _text_hpp
#define _text_hpp

class TextObject : public GameObject {
private:
	std::string text_;
	std::vector<Sprite*> sprites_;
	bool is_new_text_ = false;

	Vector2f position_;
	float scale_factor_;
	Color filter_;
	float width_ = 0;

	const std::map<char, unsigned> spec_chars_{
		{',', CHAR_COMMA_X},
		{'.', CHAR_DOT_X},
		{')', CHAR_BRACKET_CLOSE_X},
		{'(', CHAR_BRACKET_OPEN_X},
		{':', CHAR_COLON_X},
		{'-', CHAR_MINUS_X},
		{'+', CHAR_PLUS_X},
		{'_', CHAR_DASH_X},
		{'!', CHAR_EXCL_X},
		{'?', CHAR_QUEST_X},
		{'%', CHAR_PERCENT_X},
		{'/', CHAR_SLASH_X},
	};

	void updateText();
public:
	TextObject(const Vector2f& p, const float sf, const Color& f);
	TextObject(const std::string& t, const Vector2f& p, const float sf, const Color& f);
	~TextObject();

	const std::string& getText();
	void setText(const std::string& value);

	const Vector2f& getPosition();
	void setPosition(const Vector2f& value);

	const float getScaleFactor();
	void setScaleFactor(const float value);

	const Color& getColor();
	void setColor(const Color& value);

	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_text_hpp
