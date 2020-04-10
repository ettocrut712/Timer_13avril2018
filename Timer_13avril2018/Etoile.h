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
	int m_iEcho;			// nombre d'echo.  Valeur provenant de la lecture du dialogue du programme. (xfert de Timer vers Etoile.cpp)

	int m_iEcho_pointeur;  // pointe vers la position du vecteur où la prochaine position sera emmagasinée (utilisé pour traces les echos).

	// pointe vers l'étoile qui est en mouvement
	int m_iEtoileActive;
	// initialise les positions de N-1 Echo à la postion initiale de l'étoile (départ du même point pour tous)
	int InitEcho(int iEcho);
	void SetLimites(int maxX, int maxY, int minX, int minY);
	void InitPosition(int posX, int posY);
	void SetVitesse(int Vx, int Vy);
	void CalculePosition( int pointeur_echo);
	void RebonditX();
	void RebonditY();
	int m_positionX[20] = { 0 };			//historique des 20 dernières positions.  Utilisé pour calculer et afficher les "echos"
	int m_positionY[20] = { 0 };
	int m_Vx;
	int m_Vy;
	int m_maxX;
	int m_maxY;
	int m_minX;
	int m_minY;
};

