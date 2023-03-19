#include "Game.hpp"
#include "TextObject.hpp"
#include <cctype>

void TextObject::updateText() {
	for (auto ch : sprites_) {
		delete ch;
	}
	sprites_.clear();

	unsigned char_x = 0;
	unsigned char_y = 0;

	for (unsigned i = 0; i < text_.length(); i++)
	{
		Sprite* ch = new Sprite(Game::getSpriteList());

		if (std::isdigit(text_[i])) {
			char_x = CHARS_WIDTH * (text_[i] - 48);
			char_y = CHARS_D_Y;
		}
		else if (std::isalpha(text_[i])) {
			char_x = CHARS_WIDTH * (std::tolower(text_[i]) - 97);
			char_y = CHARS_L_Y;
		}
		else if (spec_chars_.contains(text_[i])) {
			char_x = spec_chars_.at(text_[i]);
			char_y = CHAR_SPEC_Y;
		}
		else {
			char_x = CHARS_WIDTH * (('z' - 97) + 1);
			char_y = CHARS_L_Y;
		}

		ch->setTextureRect(IntRect(char_x, char_y, CHARS_WIDTH, CHARS_HEIGHT));
		ch->setScale(scale_factor_, scale_factor_);
		ch->setPosition(
			position_.x + width_ * i,
			position_.y
		);
		ch->setColor(filter_);

		sprites_.push_back(ch);
	}

	is_new_text_ = false;
}

TextObject::TextObject(const Vector2f& p, const float sf, const Color& f) {
	position_ = p;
	scale_factor_ = sf;
	filter_ = f;

	width_ = scale_factor_ * CHARS_WIDTH;
}
TextObject::TextObject(const std::string& t, const Vector2f& p, const float sf, const Color& f) :TextObject(p, sf, f) {
	text_ = t;
	is_new_text_ = true;
}

TextObject::~TextObject() {
	for (auto ch : sprites_) {
		delete ch;
	}
	sprites_.clear();
}

const std::string& TextObject::getText() {
	return text_;
}
void TextObject::setText(const std::string& value) {
	text_ = value;
	is_new_text_ = true;
}

const Vector2f& TextObject::getPosition() {
	return position_;
}
void TextObject::setPosition(const Vector2f& value) {
	if (sprites_.size()) {
		float x = value.x - position_.x;
		float y = value.y - position_.y;

		for (auto ch : sprites_) {
			ch->setPosition(
				ch->getPosition().x + x,
				ch->getPosition().y + y
			);
		}
	}
	position_ = value;
}

const float TextObject::getScaleFactor() {
	return scale_factor_;
}
void TextObject::setScaleFactor(const float value) {
	scale_factor_ = value;
	float new_width = scale_factor_ * CHARS_WIDTH;

	if (sprites_.size()) {
		float x_offset = new_width - width_;

		sprites_[0]->setScale(scale_factor_, scale_factor_);

		for (unsigned i = 1; i < sprites_.size(); i++)
		{
			sprites_[i]->setScale(scale_factor_, scale_factor_);
			sprites_[i]->setPosition(
				sprites_[i]->getPosition().x + x_offset * i,
				sprites_[i]->getPosition().y
			);
		}
	}

	width_ = new_width;
}

const Color& TextObject::getColor() {
	return filter_;
}
void TextObject::setColor(const Color& value) {
	filter_ = value;

	if (sprites_.size()) {
		for (auto ch : sprites_) {
			ch->setColor(filter_);
		}
	}
}


void TextObject::fixedUpdate() {
	if (is_new_text_) {
		updateText();
	}
}

void TextObject::draw(RenderTarget& target, RenderStates states) const {
	for (auto ch : sprites_) {
		target.draw(*ch, states);
	}
}