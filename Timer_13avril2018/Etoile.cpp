#include "stdafx.h"
#include "Etoile.h"


CEtoile::CEtoile()
	: m_iID(0)					// ID de l'�toile
	, m_iEcho(0)				// nombre de positions ant�rieures  � conserver et afficher
	, m_iEtoileActive(0)		// indique quelle �toile dans l'array est l'�toile en mouvement
	, m_positionX(0)			// position de l'�toile en mouvement
	, m_positionY(0)			// position Y de l'�toile en mouvement
	, m_Vx(0)					// vitesse en X 
	, m_Vy(0)					// vitesse en Y
	, m_maxX(0)					// position maximale en X de l'aire � dessiner
	, m_maxY(0)					// position maximale en Y de l'aire � dessiner
	, m_minX(0)					// position minimale en X de l'aire � dessiner
	, m_minY(0)					// position minimale en Y de l'aire � dessiner

{
}


CEtoile::~CEtoile()
{
}


// initialise les positions de N-1 Echo � la postion initiale de l'�toile (d�part du m�me point pour tous)
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
	// positionne le point de d�part au centre de l'aire pour d�buter.  Versions futures, la position sera d�termin�e ailleurs...

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
