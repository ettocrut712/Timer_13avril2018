#pragma once
#include "afx.h"
class CEtoile :
	public CObject
{
public:
	CEtoile();
	~CEtoile();
	int m_iID;

	// nombre d'echo à afficher
	int m_iEcho;

	// pointe vers l'étoile qui est en mouvement
	int m_iEtoileActive;
	// initialise les positions de N-1 Echo à la postion initiale de l'étoile (départ du même point pour tous)
	int InitEcho();
	void SetLimites(int maxX, int maxY, int minX, int minY);
	void InitPosition(int posX, int posY);
	void SetVitesse(int Vx, int Vy);
	void CalculePosition();
	void RebonditX();
	void RebonditY();
	int m_positionX;
	int m_positionY;
	int m_Vx;
	int m_Vy;
	int m_maxX;
	int m_maxY;
	int m_minX;
	int m_minY;
};

