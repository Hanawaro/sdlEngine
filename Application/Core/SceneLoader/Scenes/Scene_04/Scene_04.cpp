#define _CRT_SECURE_NO_WARNINGS
#include "Scene_04.hpp"

#include <fstream>

#define TMP_BUFFER_SIZE	255

#define AMOUNT_OF_POINTS	"AMOUNT_OF_POINTS"
#define A_PARAMETER			"A_PARAMETER"
#define B_PARAMETER			"B_PARAMETER"
#define LEFT_X_POSITION		"LEFT_X_POSITION"
#define RIGHT_X_POSITION	"RIGHT_X_POSITION"

#define MARGING_X	30
#define MARGING_Y	30

#define PIXEL_Y		10
#define PIXEL_X		10

#define MINIMAL_POINT_X	2

Scene_04::Scene_04(void) {}

Scene_04::~Scene_04(void) {
	Clear();
}

void Scene_04::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	// Set window parameters
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	// Init render block
	SDL_SetRenderDrawColor(m_Renderer, 250, 240, 240, 255);
	SDL_RenderClear(m_Renderer);

	// Reading the config
	if (readCfg(std::string(PATH))) {
		Logger::LogSucsess(std::string("The config is read"));
		m_isConfig = true;

		// Mouse settings
		m_Sys.t_MouseX = new TextEntity("Application/Source/Font/arial_b.ttf", 14, { 0, 0, 0 }, transToDouble(m_Mouse.posX), m_Renderer);
		m_Sys.t_MouseY = new TextEntity("Application/Source/Font/arial_b.ttf", 14, { 0, 0, 0 }, transToDouble(m_Mouse.posY), m_Renderer);

		// Tune settings
		tune();
	} else {
		Logger::LogError(std::string("Failed to read the config"));
		m_isConfig = false;
		stdDraw();
	}
	
	m_Status = true;
}

void Scene_04::Clear(void) {
	delete[] m_Graph.valeus;
	delete m_Sys.t_Left;
	delete m_Sys.t_Right;
	delete m_Sys.t_Up;
	delete m_Sys.t_Down;
	delete m_Sys.t_Center;
	delete m_Sys.t_MouseX;
	delete m_Sys.t_MouseY;

	// Set all by default
	m_Graph = { UINT16_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX };
	m_Sys = {
		DBL_MAX, DBL_MAX, INT16_MIN, INT16_MAX,
		DBL_MAX, DBL_MAX,
		DBL_MAX, DBL_MAX,
		DBL_MAX, DBL_MAX,
		nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr
	};
	m_Mouse = { -1000, -1000 };
	m_Status = false;
}

void Scene_04::HandleEvent(SDL_Event* l_Event) {
	switch (l_Event->type) {
	case SDL_MOUSEMOTION:
		m_Mouse.posX = (int)(l_Event->motion.x - m_Sys.needToOy);
		m_Mouse.posY = (int)(l_Event->motion.y - m_Sys.needToOx);
		break;
	default:
		break;
	}
}

void Scene_04::Draw(void) {
	SDL_SetRenderDrawColor(m_Renderer, 250, 240, 240, 255);
	SDL_RenderClear(m_Renderer);

	if (m_isConfig) {
		SDL_SetRenderDrawColor(m_Renderer, 250, 240, 240, 255);
		SDL_RenderClear(m_Renderer);

		// To Ox
		double koef = 1;

		while (m_Sys.pixel_stepX * koef < PIXEL_X) {
			koef++;
		}
		while (m_Sys.pixel_stepX * 2 * koef > abs(m_Sys.needToOy)) {
			koef /= 2;
		}

		for (double i = m_Sys.needToOy; i >= 0; i -= m_Sys.pixel_stepX * koef) {
			lineRGBA(
				m_Renderer,
				(int)(i), 0,
				(int)(i), m_Window->height,
				200, 200, 200, 255
			);
		}
		for (double i = m_Sys.needToOy; i <= m_Window->width; i += m_Sys.pixel_stepX * koef) {
			lineRGBA(
				m_Renderer,
				(int)(i), 0,
				(int)(i), m_Window->height,
				200, 200, 200, 255
			);
		}

		// To Oy
		koef = 1;

		while (m_Sys.pixel_stepY * koef < PIXEL_Y) {
			koef++;
		}
		while (m_Sys.pixel_stepY * 4 * koef > abs(m_Sys.needToOx)) {
			koef /= 2;
		}

		for (double i = m_Sys.needToOx; i >= 0; i -= m_Sys.pixel_stepY * koef) {
			lineRGBA(
				m_Renderer,
				0, (int)(i),
				m_Window->width, (int)(i),
				200, 200, 200, 255
			);
		}
		for (double i = m_Sys.needToOx; i <= m_Window->height; i += m_Sys.pixel_stepY * koef) {
			lineRGBA(
				m_Renderer,
				0, (int)(i),
				m_Window->width, (int)(i),
				200, 200, 200, 255
			);
		}

		// Ox
		for (int i = 0; i <= 1; i++)
			lineRGBA(
				m_Renderer,
				0, (int)(m_Sys.needToOx + i),
				m_Window->width, (int)(m_Sys.needToOx + i),
				0, 0, 0, 255
			);
		filledTrigonRGBA(
			m_Renderer,
			m_Window->width, (int)(m_Sys.needToOx),
			m_Window->width - 15, (int)(m_Sys.needToOx - 4),
			m_Window->width - 15, (int)(m_Sys.needToOx + 4),
			0, 0, 0, 255
		);
		// Oy
		for (int i = 0; i <= 1; i++)
			lineRGBA(
				m_Renderer,
				(int)(m_Sys.needToOy + i), 0,
				(int)(m_Sys.needToOy + i), m_Window->height,
				0, 0, 0, 255
			);
		filledTrigonRGBA(
			m_Renderer,
			(int)(m_Sys.needToOy), 0,
			(int)(m_Sys.needToOy - 4), 15,
			(int)(m_Sys.needToOy + 4), 15,
			0, 0, 0, 255
		);
		// Graph
		for (int i = 0; i < m_Graph.AmoutOfPointer - 1; i++) {
			lineRGBA(
				m_Renderer,
				(int)(m_Sys.needToOy + m_Graph.valeus[i] * m_Sys.pixel_stepX), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer] * m_Sys.pixel_stepY),
				(int)(m_Sys.needToOy + m_Graph.valeus[i + 1] * m_Sys.pixel_stepX), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer + 1] * m_Sys.pixel_stepY),
				255, 0, 0, 255
			);
			lineRGBA(
				m_Renderer,
				(int)(m_Sys.needToOy + m_Graph.valeus[i] * m_Sys.pixel_stepX + 1), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer] * m_Sys.pixel_stepY),
				(int)(m_Sys.needToOy + m_Graph.valeus[i + 1] * m_Sys.pixel_stepX + 1), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer + 1] * m_Sys.pixel_stepY),
				255, 0, 0, 255
			);
			lineRGBA(
				m_Renderer,
				(int)(m_Sys.needToOy + m_Graph.valeus[i] * m_Sys.pixel_stepX), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer] * m_Sys.pixel_stepY + 1),
				(int)(m_Sys.needToOy + m_Graph.valeus[i + 1] * m_Sys.pixel_stepX), (int)(m_Sys.needToOx - m_Graph.valeus[i + m_Graph.AmoutOfPointer + 1] * m_Sys.pixel_stepY + 1),
				255, 0, 0, 255
			);
		}

		// Draw text
		m_Sys.t_Center->Draw(
			m_Renderer,
			(int)(m_Sys.needToOy - m_Sys.t_Center->GetDstRect()->w - 5),
			(int)(m_Sys.needToOx - m_Sys.t_Center->GetDstRect()->h - 5)
		);
		m_Sys.t_Left->Draw(
			m_Renderer,
			(int)(m_Sys.needToOy - m_Sys.t_Left->GetDstRect()->w / 2 - abs(m_Sys.left) * m_Sys.pixel_stepX),
			(int)(m_Sys.needToOx + m_Sys.t_Left->GetDstRect()->h - 4)
		);
		m_Sys.t_Right->Draw(
			m_Renderer,
			(int)(m_Sys.needToOy - m_Sys.t_Right->GetDstRect()->w / 2 + abs(m_Sys.right) * m_Sys.pixel_stepX),
			(int)(m_Sys.needToOx + m_Sys.t_Right->GetDstRect()->h - 4)
		);
		m_Sys.t_Up->Draw(
			m_Renderer,
			(int)(m_Sys.needToOy + 6),
			(int)(m_Sys.needToOx - m_Sys.t_Up->GetDstRect()->h / 2 - abs(m_Sys.up) * m_Sys.pixel_stepY)
		);
		m_Sys.t_Down->Draw(
			m_Renderer,
			(int)(m_Sys.needToOy + 6),
			(int)(m_Sys.needToOx + m_Sys.t_Down->GetDstRect()->h / 2 + abs(m_Sys.down) * m_Sys.pixel_stepY)
		);


		// Draw mouse
		if (m_Mouse.posX + m_Sys.needToOy >= 10 && m_Mouse.posX + m_Sys.needToOy <= m_Window->width - 10 &&
			m_Mouse.posY + m_Sys.needToOx >= 10 && m_Mouse.posY + m_Sys.needToOx <= m_Window->height - 10) {
			m_Sys.t_MouseX->SetContent(transToDouble(m_Mouse.posX / m_Sys.pixel_stepX), m_Renderer);
			m_Sys.t_MouseY->SetContent(transToDouble(- m_Mouse.posY / m_Sys.pixel_stepY), m_Renderer);
			bool leftLimitXY = false,
				downLimitXY = false;
			if (m_Mouse.posX + m_Sys.needToOy + m_Sys.t_MouseX->GetDstRect()->w + 8 + m_Sys.t_MouseY->GetDstRect()->w >= m_Window->width) {
				leftLimitXY = true;
			}
			if (m_Mouse.posY + m_Sys.needToOx + 20 + m_Sys.t_MouseX->GetDstRect()->h >= m_Window->height) {
				downLimitXY = true;
			}
			m_Sys.t_MouseX->Draw(m_Renderer,
				(int)(leftLimitXY ? m_Mouse.posX + m_Sys.needToOy - 8 - m_Sys.t_MouseX->GetDstRect()->w - m_Sys.t_MouseY->GetDstRect()->w : m_Mouse.posX + m_Sys.needToOy + 4),
				(int)(downLimitXY ? m_Mouse.posY + m_Sys.needToOx - 15 : m_Mouse.posY + m_Sys.needToOx + 20)
			);
			m_Sys.t_MouseY->Draw(
				m_Renderer,
				(int)(leftLimitXY ? m_Mouse.posX + m_Sys.needToOy - 4 - m_Sys.t_MouseY->GetDstRect()->w : m_Mouse.posX + m_Sys.needToOy + m_Sys.t_MouseX->GetDstRect()->w + 8),
				(int)(downLimitXY ? m_Mouse.posY + m_Sys.needToOx - 15 : m_Mouse.posY + m_Sys.needToOx + 20)
			);
		} 

	} else {
		stdDraw();
	}
	SDL_RenderPresent(m_Renderer);
}

void Scene_04::Update(double l_Time) {
}

bool Scene_04::readCfg(const std::string& l_Path) {
	Logger::LogImportant(std::string("Reading the ") + l_Path);
	// Open the config
	FILE* cfg = fopen(l_Path.c_str(), "rt");
	// Check open status
	if (!cfg) {
		Logger::LogError(std::string("Could not read ") + l_Path);
		return false;
	}

	char tmp_Buffer[TMP_BUFFER_SIZE] = "\0";
	int statusOfRead = 0;
	bool statusOfPars = true;

	// Read each line
	do {
		if ((statusOfRead = readLine(cfg, tmp_Buffer)) != 2) {
			statusOfPars = parsLine(tmp_Buffer);
		} else {
			statusOfRead = 0;
			statusOfPars = true;
		}
	} while (!statusOfRead && statusOfPars);

	// Close file connection
	fclose(cfg);
	
	// Check errors
	if (statusOfRead == -1) {
		Logger::LogError(std::string("Stack overflow in ") + l_Path);
		return false;
	} else if (!statusOfPars) {
		Logger::LogError(std::string("Incorrect data in ") + l_Path);
		return false;
	} else if (m_Graph.left >= m_Graph.right) {
		Logger::LogError(std::string("Incorrect rande of values in ") + l_Path);
		return false;
	}

	return true;
}

int Scene_04::readLine(FILE* l_cfg, char* l_Buffer) {
	int indexOfBuffer = 0;
	int ch = '\0';
	
	// Read until we get the end of the file or line or just comment
	for (ch = (int)(fgetc(l_cfg)); ch != EOF && ch != (int)('\n'); ch = (int)(fgetc(l_cfg))) {
		// Delete all spaces
		if (ch == ' ' || ch == '\t') continue;
		// Delete comments
		if (ch == '#') {
			while ( (ch = (int)(fgetc(l_cfg))) != EOF && ch != '\n');
			break;
		}
		// Check stack overflow
		if (indexOfBuffer >= TMP_BUFFER_SIZE) {
			l_Buffer[0] = '\0';
			return -1;
		}
		// Copy line
		l_Buffer[indexOfBuffer++] = char(ch);
	}
	// Take \0 symbol to future correct work
	l_Buffer[indexOfBuffer] = '\0';
	// The end of the file
	if (ch == EOF)
		return 1;
	// Empty line
	if (!indexOfBuffer)
		return 2;
	return 0;
}

bool Scene_04::parsLine(const char* l_Buffer) {
	char tmp_Buffer[TMP_BUFFER_SIZE] = "\0";
	int indexOfParameter = 0;

	// Read the parameter of the line
	while (l_Buffer[indexOfParameter] != '\0' && l_Buffer[indexOfParameter] != '=') {
		tmp_Buffer[indexOfParameter] = l_Buffer[indexOfParameter];
		indexOfParameter++;
	}

	// If after the parameter nothing is
	if (l_Buffer[indexOfParameter] == '\0') {
		Logger::LogError(std::string("Incorrect data"));
		return false; 
	}

	// Add zero symbol to correct work
	tmp_Buffer[indexOfParameter++] = '\0';

	/* 
		Check reserved words 
	*/

	// amount of points
	if (std::string(tmp_Buffer) == AMOUNT_OF_POINTS) {
		char ch = '\0';
		int indexOfValue = 0;
		while ((ch = l_Buffer[indexOfParameter++]) >= '0' && ch <= '9' && ch != '\0') {
			tmp_Buffer[indexOfValue++] = ch;
		}

		// No value
		if (ch != '\0') {
			Logger::LogError(std::string("Incorrect value of parameter \"AMOUNT_OF_POINTS\""));
			return false;
		}
		tmp_Buffer[indexOfValue] = '\0';
		m_Graph.AmoutOfPointer = atoi(tmp_Buffer);

		// Incorrect value
		if (m_Graph.AmoutOfPointer <= MINIMAL_POINT_X) {
			Logger::LogError(std::string("Incorerct amount of points "));
			return false;
		}
		return true;
	// a parameter
	} else if (std::string(tmp_Buffer) == A_PARAMETER) {
		char ch = '\0';
		int indexOfValue = 0;
		while ( ( ((ch = l_Buffer[indexOfParameter++]) >= '0' && ch <= '9') || ch == '.' || ch == ',' || ch == '-') && ch != '\0') {
			tmp_Buffer[indexOfValue++] = ch;
		}

		// No value
		if (ch != '\0') {
			Logger::LogError(std::string("Incorrect value of parameter \"A_PARAMETER\""));
			return false;
		}
		tmp_Buffer[indexOfValue] = '\0';
		m_Graph.a = atof(tmp_Buffer);
		
		// Incorrect value
		if (m_Graph.a == 0) {
			Logger::LogError(std::string("A parameter cannot be zero "));
			return false;
		}
		return true;
	// b parameter
	} else if (std::string(tmp_Buffer) == B_PARAMETER) {
		char ch = '\0';
		int indexOfValue = 0;
		while ((((ch = l_Buffer[indexOfParameter++]) >= '0' && ch <= '9') || ch == '.' || ch == ',' || ch == '-') && ch != '\0') {
			tmp_Buffer[indexOfValue++] = ch;
		}

		// No value
		if (ch != '\0') {
			Logger::LogError(std::string("Incorrect value of parameter \"B_PARAMETER\""));
			return false;
		}
		tmp_Buffer[indexOfValue] = '\0';
		m_Graph.b = atof(tmp_Buffer);
		return true;
	// left x position
	} else if (std::string(tmp_Buffer) == LEFT_X_POSITION) {
		char ch = '\0';
		int indexOfValue = 0;
		while ((((ch = l_Buffer[indexOfParameter++]) >= '0' && ch <= '9') || ch == '.' || ch == ',' || ch == '-') && ch != '\0') {
			tmp_Buffer[indexOfValue++] = ch;
		}

		// No value
		if (ch != '\0') {
			Logger::LogError(std::string("Incorrect value of parameter \"LEFT_X_POSITION\""));
			return false;
		}
		tmp_Buffer[indexOfValue] = '\0';
		m_Graph.left = atof(tmp_Buffer);
		return true;
	// right x position
	} else if (std::string(tmp_Buffer) == RIGHT_X_POSITION) {
		char ch = '\0';
		int indexOfValue = 0;
		while ((((ch = l_Buffer[indexOfParameter++]) >= '0' && ch <= '9') || ch == '.' || ch == ',' || ch == '-') && ch != '\0') {
			tmp_Buffer[indexOfValue++] = ch;
		}

		// No value
		if (ch != '\0') {
			Logger::LogError(std::string("Incorrect value of parameter \"RIGHT_X_POSITION\""));
			return false;
		}
		tmp_Buffer[indexOfValue] = '\0';
		m_Graph.right = atof(tmp_Buffer);
		return true;
	// nothing
	} else {
		Logger::LogError(std::string("Incorrect parameter"));
		return false;
	}
	return true;
}

void Scene_04::tune(void) {
	// Set m_Sys
	m_Sys.left = m_Graph.left;
	m_Sys.right = m_Graph.right;

	/*
	=================================================

		Setting Oy if u want to ceil the interval

	=================================================
	*/
	/*
		if (m_Sys.left < 0 && m_Sys.right > 0) {
			m_Sys.pixel_stepX = (m_Window->width - 2 * MARGING_X) / (ceil(m_Sys.right) + ceil(abs(m_Sys.left)));
			m_Sys.needToOy = -m_Sys.left * m_Sys.pixel_stepX + MARGING_X + ((ceil(m_Sys.right) + ceil(abs(m_Sys.left))) - (m_Sys.right - m_Sys.left)) * m_Sys.pixel_stepX / 2;
		} else if ( m_Sys.left >= 0) {
			m_Sys.pixel_stepX = (m_Window->width - 2 * MARGING_X) / (ceil(m_Sys.right) - floor(abs(m_Sys.left)));
			m_Sys.needToOy = -m_Sys.left * m_Sys.pixel_stepX + MARGING_X - ((ceil(m_Sys.right) - floor(abs(m_Sys.left))) - (m_Sys.right - m_Sys.left)) * m_Sys.pixel_stepX / 2;
		} else {
			m_Sys.pixel_stepX = (m_Window->width - 2 * MARGING_X) / (-floor(abs(m_Sys.right)) + ceil(abs(m_Sys.left)));
			m_Sys.needToOy = -m_Sys.left * m_Sys.pixel_stepX + MARGING_X + ((-floor(abs(m_Sys.right)) + ceil(abs(m_Sys.left))) - (m_Sys.right - m_Sys.left)) * m_Sys.pixel_stepX / 2;
		}
	*/
	m_Sys.pixel_stepX = (m_Window->width - 2 * MARGING_X) / (m_Sys.right - m_Sys.left);
	m_Sys.needToOy = - m_Sys.left * m_Sys.pixel_stepX + MARGING_X;
	// INSTEAD OF THIS

	m_Sys.point_stepX = (m_Sys.right - m_Sys.left) / (m_Graph.AmoutOfPointer - 1);

	// Find maximal and minimal on Oy
	m_Sys.up = INT16_MIN;
	m_Sys.down = INT16_MAX;
	for (double i = 0; i < m_Graph.AmoutOfPointer; i++) {
		double value = m_Graph.a * (i * m_Sys.point_stepX + m_Sys.left) * (i * m_Sys.point_stepX + m_Sys.left) + m_Graph.b;
		if (value < m_Sys.down)
			m_Sys.down = value;
		if (value > m_Sys.up)
			m_Sys.up = value;
	}

	/* 
	=================================================

		Setting Oy if u want to ceil the interval

	================================================= 
	*/
	/*
		if (m_Sys.down < 0 && m_Sys.up > 0) {
			m_Sys.pixel_stepY = (m_Window->height - 2 * MARGING_Y) / (ceil(m_Sys.up) + ceil(abs(m_Sys.down)));
			m_Sys.needToOx = m_Sys.up * m_Sys.pixel_stepY + MARGING_Y + ((ceil(m_Sys.up) + ceil(abs(m_Sys.down))) - (m_Sys.up - m_Sys.down)) * m_Sys.pixel_stepY / 2;
		} else if (m_Sys.down >= 0) {
			m_Sys.pixel_stepY = (m_Window->height - 2 * MARGING_Y) / (ceil(m_Sys.up) - floor(abs(m_Sys.down)));
			m_Sys.needToOx = m_Sys.up * m_Sys.pixel_stepY + MARGING_Y + ((ceil(m_Sys.up) - floor(abs(m_Sys.down))) - (m_Sys.up - m_Sys.down)) * m_Sys.pixel_stepY / 2;
		} else {
			m_Sys.pixel_stepY = (m_Window->height - 2 * MARGING_Y) / (-floor(abs(m_Sys.up)) + ceil(abs(m_Sys.down)));
			m_Sys.needToOx = m_Sys.up * m_Sys.pixel_stepY + MARGING_Y + ((-floor(abs(m_Sys.up)) + ceil(abs(m_Sys.down))) - (m_Sys.up - m_Sys.down)) * m_Sys.pixel_stepY / 2;
		}
	*/
	m_Sys.pixel_stepY = (m_Window->height - 2 * MARGING_Y) / (m_Sys.up - m_Sys.down);
	m_Sys.needToOx = m_Sys.up * m_Sys.pixel_stepY + MARGING_Y;
	// INSTEAD OF THIS

	// Set values (x, y)
	m_Graph.valeus = new double[m_Graph.AmoutOfPointer * 2];
	double left = m_Sys.left;
	for (int i = 0; i < m_Graph.AmoutOfPointer; i++, left += m_Sys.point_stepX) {
		m_Graph.valeus[i] = left;
		m_Graph.valeus[i + m_Graph.AmoutOfPointer] = m_Graph.a * left * left + m_Graph.b;
	}

	// Text
	m_Sys.t_Center = new TextEntity("Application/Source/Font/arial.ttf", 14, { 0, 0, 0 }, transToInt(0), m_Renderer);
	m_Sys.t_Left = new TextEntity("Application/Source/Font/arial.ttf", 14, { 0, 0, 0 }, transToDouble(m_Sys.left), m_Renderer);
	m_Sys.t_Right = new TextEntity("Application/Source/Font/arial.ttf", 14, { 0, 0, 0 }, transToDouble(m_Sys.right), m_Renderer);
	m_Sys.t_Up = new TextEntity("Application/Source/Font/arial.ttf", 14, { 0, 0, 0 }, transToDouble(m_Sys.up), m_Renderer);
	m_Sys.t_Down = new TextEntity("Application/Source/Font/arial.ttf", 14, { 0, 0, 0 }, transToDouble(m_Sys.down), m_Renderer);
}

void Scene_04::stdDraw(void) {
	m_Sys.needToOx = MARGING_Y + (m_Window->height - 2 * MARGING_Y) / 2;
	m_Sys.needToOy = MARGING_X + (m_Window->width - 2 * MARGING_X) / 2;

	// To Ox
	for (double i = m_Sys.needToOy; i >= 0; i -= PIXEL_X) {
		lineRGBA(
			m_Renderer,
			Sint16(i), 0,
			Sint16(i), m_Window->height,
			200, 200, 200, 255
		);
	}
	for (double i = m_Sys.needToOy; i <= m_Window->width; i += PIXEL_X) {
		lineRGBA(
			m_Renderer,
			Sint16(i), 0,
			Sint16(i), m_Window->height,
			200, 200, 200, 255
		);
	}

	// To Oy
	for (double i = m_Sys.needToOx; i >= 0; i -= PIXEL_Y) {
		lineRGBA(
			m_Renderer,
			0, Sint16(i),
			m_Window->width, Sint16(i),
			200, 200, 200, 255
		);
	}
	for (double i = m_Sys.needToOx; i <= m_Window->height; i += PIXEL_Y) {
		lineRGBA(
			m_Renderer,
			0, Sint16(i),
			m_Window->width, Sint16(i),
			200, 200, 200, 255
		);
	}

	// Ox
	filledTrigonRGBA(
		m_Renderer,
		m_Window->width, Sint16(m_Sys.needToOx),
		m_Window->width - 15, Sint16(m_Sys.needToOx + 4),
		m_Window->width - 15, Sint16(m_Sys.needToOx - 4),
		0, 0, 0, 255
	);
	for (int i = 0; i <= 1; i++) {
		lineRGBA(
			m_Renderer,
			0, Sint16(m_Sys.needToOx + i),
			m_Window->width, Sint16(m_Sys.needToOx + i),
			0, 0, 0, 255
		);
	}

	// Oy
	filledTrigonRGBA(
		m_Renderer,
		Sint16(m_Sys.needToOy), 0,
		Sint16(m_Sys.needToOy + 4), 15,
		Sint16(m_Sys.needToOy - 4), 15,
		0, 0, 0, 255
	);
	for (int i = 0; i <= 1; i++) {
		lineRGBA(
			m_Renderer,
			Sint16(m_Sys.needToOy + i), 0,
			Sint16(m_Sys.needToOy + i), m_Window->height,
			0, 0, 0, 255
		);
	}
}

const std::string Scene_04::transToDouble(double l_Value) {
	std::stringstream tmp_ss;
	std::string result;
	tmp_ss.precision(2);
	tmp_ss << std::fixed << l_Value;
	tmp_ss >> result;
	return result;
}

const std::string Scene_04::transToInt(Uint16 l_Value) {
	std::stringstream tmp_ss;
	std::string result;
	tmp_ss << l_Value;
	tmp_ss >> result;
	return result;
}
