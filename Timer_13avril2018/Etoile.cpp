#include "stdafx.h"
#include "Etoile.h"


CEtoile::CEtoile()
	: m_iID(0)					// ID de l'étoile
	, m_iEcho(0)				// nombre de positions antérieures  à conserver et afficher
	, m_iEtoileActive(0)		// indique quelle étoile dans l'array est l'étoile en mouvement
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
int CEtoile::InitEcho(int iEcho)
{
	
	m_iEtoileActive = 0;
	m_iEcho = iEcho;  // iEcho est le nombre d'Echo provenant du dialogue du programme.

	for (int i = 0; i < iEcho; i++)
	{
		m_positionX[i] = m_Vx + m_positionX[0];
		m_positionY[i] = m_Vy + m_positionY[0];
	};


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

	int i;
	for (i = 0; i < m_iEcho; i++)
	{

		m_positionX[i] = posX;
		m_positionY[i] = posY;

	};
}


void CEtoile::SetVitesse(int Vx, int Vy)
{
	
	m_Vx = Vx;
	m_Vy = Vy;
}


void CEtoile::CalculePosition(int pointeur_echo)
{

	if (pointeur_echo != 0)
	{
		m_positionX[pointeur_echo] = m_Vx + m_positionX[pointeur_echo - 1];
		m_positionY[pointeur_echo] = m_Vy + m_positionY[pointeur_echo - 1];
	}
	else
	{
		m_positionX[pointeur_echo] = m_Vx + m_positionX[m_iEcho-1];
		m_positionY[pointeur_echo] = m_Vy + m_positionY[m_iEcho-1];
		

	};


	if (m_positionX[pointeur_echo] > m_maxX )

	{
		m_positionX[pointeur_echo] = m_maxX;
		RebonditX();

	};

	if (m_positionX[pointeur_echo]  < m_minX)

	{
		m_positionX[pointeur_echo] = m_minX;
		RebonditX();

	}

	if (m_positionY[pointeur_echo] > m_maxY )
	{
		m_positionY[pointeur_echo] = m_maxY;
		RebonditY();

	}
	if (m_positionY[pointeur_echo]  < m_minY)
	{
		m_positionY[pointeur_echo] = m_minY;
		RebonditY();

	}
	m_iEcho_pointeur = pointeur_echo;
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
