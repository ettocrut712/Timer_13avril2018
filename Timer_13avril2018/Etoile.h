#pragma once
#include "afx.h"
#include <array>

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
	void SetLimites(int maxX, int maxY, int minX, int minY, int minZ, int maxZ);
	void InitPosition(int posX, int posY, int posZ);
	void SetVitesse(float Vx, float Vy, float Vz);
	void VerifieLimites(int m_pointeur_echo);
	void Deplace(int m_pointeur_echo);
	void RebonditX();
	void RebonditY();
	void Rotation();
	void Translation();
	void UpdateDistance(int distance, float cos_teta, int direction);
	void CorrectionTrajectoire();
	void SetDistanceLeader(int distance, float m_direction_leader);
	//void SetD1_D2(int D1, int D2);
	bool m_3D_enabled;
	void Set3D(bool m_3D);

	int m_D1=100, m_D2=80;									// distances entre les objets qui forcent une correction de trajectoire.

	struct pair_coord { int x; int y; };
	int m_positionX[50] = { 0 };							//historique des 20 dernières positions.  Utilisé pour calculer et afficher les "echos"
	int m_positionY[50] = { 0 };
	int m_positionZ[50] = { 0 };

	float m_Vx, m_Vy,m_Vz, m_V;								//vitesse de l'objet (x,y,z total)

	float m_cosTeta, m_sinTeta;								//angle entre l'objet en mouvement et l'objet le plus pres.  cosDelta 
	float m_Teta_leader;
	float m_cosVitesse, m_sinVitesse;						// orientation de la tete (graphique) Teta = angle de deplacement,  Delta: angle entre la direction de l'objet et l'obstacle le plus pres...
	int m_direction;
	
	int m_maxX;												///m_maxXY: dimensions des limites du jeu
	int m_maxY;
	int m_maxZ;

	int m_minX;
	int m_minY;
	int m_minZ;
	float m_distance_leader;
	int m_direction_leader;

	int m_distance_gauche;
	int m_distance_devant;
	int m_distance_droite;
	int m_niveau_correction=0;								// o: aucune correction appliquée.  1: premiere correction appliquée, 2: 2eme correction appliquée, 3, 4, 5.  Permet d'éviter de répéter la même correction plusieurs fois 
	std::array<pair_coord, 3> m_tete_coordonnees;			// coordonnes de la tete (utilise pour rotation et translation de la tete et dessiner...
	

};

