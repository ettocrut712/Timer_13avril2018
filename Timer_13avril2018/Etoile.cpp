#include "stdafx.h"
#include "Etoile.h"


CEtoile::CEtoile()
	: m_iID(0)					// ID de l'étoile
	, m_iEcho(0)				// nombre de positions antérieures  à conserver et afficher
	, m_iEtoileActive(0)		// indique quelle étoile dans l'array est l'étoile en mouvement
	, m_positionX(0)			// position de l'étoile en mouvement
	, m_positionY(0)			// position Y de l'étoile en mouvement
	, m_Vx(0)					// vitesse en X 
	, m_Vy(0)					// vitesse en Y
	, m_maxX(0)					// position maximale en X de l'aire à dessiner
	, m_maxY(0)					// position maximale en Y de l'aire à dessiner
	, m_minX(0)					// position minimale en X de l'aire à dessiner
	, m_minY(0)					// position minimale en Y de l'aire à dessiner

{
}


CEtoile::~CEtoile()
{
}


// initialise les positions de N-1 Echo à la postion initiale de l'étoile (départ du même point pour tous)
int CEtoile::InitEcho()
{
	return 0;
}


void CEtoile::SetLimites(int maxX, int maxY, int minX, int minY)
{
	m_maxX = maxX;
	m_maxY = maxY;
	m_minX = minX;
	m_minY = minY;
}


void CEtoile::InitPosition(int posX, int posY)
{
	// positionne le point de départ au centre de l'aire pour débuter.  Versions futures, la position sera déterminée ailleurs...

	m_positionX = posX;
	m_positionY = posY;
}


void CEtoile::SetVitesse(int Vx, int Vy)
{
	
	m_Vx = Vx;
	m_Vy = Vy;
}


void CEtoile::CalculePosition()
{
	m_positionX += m_Vx;
	m_positionY += m_Vy;

	if (m_positionX > m_maxX || m_positionX < m_minX)

	{
		m_positionX -= m_Vx;
		RebonditX();

	}

	if (m_positionY > m_maxY || m_positionY < m_minY)
	{
		m_positionY -= m_Vy;
		RebonditY();

	}

	


	}


void CEtoile::RebonditX()
{

	// changement de vitesse et de direction
	if (m_Vx > 0)
	{
		m_Vx = -1 * rand() % 20;
		if (m_Vx == 0)m_Vx = -1;
	}
	else
	{
		m_Vx = rand() % 20; 
		if (m_Vx == 0)m_Vx = 1;
	}
}


void CEtoile::RebonditY()
{
	// changement de vitesse et de direction
	if (m_Vy > 0)
	{
		m_Vy = -1 * rand() % 20;
		if (m_Vy == 0)m_Vy = -1;
	}
	else
	{
		m_Vy = rand() % 20;
		if (m_Vy == 0)m_Vy = 1;
	}


}
