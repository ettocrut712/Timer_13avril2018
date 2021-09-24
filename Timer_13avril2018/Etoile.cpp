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

void CEtoile::Rotation()
{
// rotation des coordonnes de la tete de l'objet: 

	// initialise la tete de l'objet avant de faire la rotation:
	int hauteur, largeur, temp_x, temp_y;
	hauteur = 7;
	largeur = 9;

	
	m_tete_coordonnees[0].x = 0;				//pointe de l'objet.  Dessine un triangle.  La pointe (0,0) et le devant de l'objet.  Centré sur l'origine pour permettre la rotation.
	m_tete_coordonnees[0].y = 0;
	m_tete_coordonnees[1].x = -largeur;			// Les deux pointes de l'objet.
	m_tete_coordonnees[1].y = -hauteur;
	m_tete_coordonnees[2].x = -largeur;
	m_tete_coordonnees[2].y =  hauteur;

	//rotation de la tete de l'objet

	for (int a = 0; a < 3; a++)
	{
		temp_x = m_tete_coordonnees[a].x;
		temp_y = m_tete_coordonnees[a].y;

		m_tete_coordonnees[a].x = m_cosVitesse * temp_x - m_sinVitesse * temp_y;
		m_tete_coordonnees[a].y = m_sinVitesse * temp_x + m_cosVitesse * temp_y;
	}

};

void CEtoile::Translation()
{
	//translation des coordonnées de la tete de l'objet: 
	
	if (m_iEcho_pointeur > -1 && m_iEcho_pointeur < m_iEcho)
	{
		m_tete_coordonnees[0].x += m_positionX[m_iEcho_pointeur];			//pointe de l'objet.
		m_tete_coordonnees[0].y += m_positionY[m_iEcho_pointeur];
		m_tete_coordonnees[1].x += m_positionX[m_iEcho_pointeur];
		m_tete_coordonnees[1].y += m_positionY[m_iEcho_pointeur];
		m_tete_coordonnees[2].x += m_positionX[m_iEcho_pointeur];
		m_tete_coordonnees[2].y += m_positionY[m_iEcho_pointeur];
	};

	

};

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


void CEtoile::SetVitesse(float Vx, float Vy)
{
	
	m_Vx = Vx;
	m_Vy = Vy;
	m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));	//vitesse de l'objet 
	
	m_cosVitesse = m_Vx/m_V;						//calcul de l'angle de rotation de l'objet.  Utilisé pour dessiner à l'écran.
	m_sinVitesse = m_Vy/m_V;
}
void CEtoile::UpdateDistance(int distance, float sin_teta, int direction)  // direction de l'obstacle: 1= gauche (sin_teta <0), 2 = droite (sin_teta >0);
{
	// Recoit une distance calculée entre cette étoile et une autre étoile et la direction (delta X, Y). Met à jour les points de distance  (devant, gauche, droite) si la distance est moindre que la distance déjà en place.
	// Les valeurs des distances sont intialisées dans le Timer_13avril2018Dlg.cpp::CalculeDistances()

	if (distance < m_distance_devant) 
	{

		m_sinTeta = sin_teta;					//angle entre la direction et un obstacle
		m_direction = direction;				
		m_distance_devant = distance;

		// calcul de la direction (obstacle à gauche=1 , droite=2)

		//(sin_teta < 0) direction = 2;
		//(sin_teta > 0) direction = 1;
	};

	

};
void CEtoile::Deplace(int pointeur_echo)
{
	if (pointeur_echo != 0)
	{
		m_positionX[pointeur_echo] = m_Vx + m_positionX[pointeur_echo - 1];
		m_positionY[pointeur_echo] = m_Vy + m_positionY[pointeur_echo - 1];
	}
	else
	{
		m_positionX[pointeur_echo] = m_Vx + m_positionX[m_iEcho - 1];
		m_positionY[pointeur_echo] = m_Vy + m_positionY[m_iEcho - 1];
	};
	m_iEcho_pointeur = pointeur_echo;
	
};


void CEtoile::VerifieLimites(int pointeur_echo)
{

	
	

	if (m_positionX[pointeur_echo] > m_maxX )

	{
		m_positionX[pointeur_echo] = m_maxX;
		this->RebonditX();

	};

	if (m_positionX[pointeur_echo]  < m_minX)

	{
		m_positionX[pointeur_echo] = m_minX;
		this->RebonditX();

	}

	if (m_positionY[pointeur_echo] > m_maxY )
	{
		m_positionY[pointeur_echo] = m_maxY;
		this->RebonditY();

	}
	if (m_positionY[pointeur_echo]  < m_minY)
	{
		m_positionY[pointeur_echo] = m_minY;
		this->RebonditY();

	}

	m_cosVitesse = m_Vx / m_V;						//calcul de l'angle de rotation de l'objet.  Utilisé pour dessiner à l'écran.
	m_sinVitesse = m_Vy / m_V;

	
};


void CEtoile::SetDistanceLeader(int distance, float teta)
{
	m_distance_leader = distance;
	if (distance < 0)
	{
		int i = 0;
		i = i + 1;
	};
	m_Teta_leader = teta;
};



void CEtoile::CorrectionTrajectoire()
{

	float temp_x = m_Vx;
	float temp_y = m_Vy;

	//sin(2)  = 0.0348995,  cos (2) = 0.999391
	//sin(5)  = 0.08715574, cos(5)  = 0.9961946981
	//sin(10) = 0.173648,   cos(10) = 0.984807
	//sin(20) = 0.34202     cos(20) = 0.939693

	if (m_distance_devant > 250) m_niveau_correction = 0;





	if (m_distance_leader > 120 && m_iID != 0 )    // si distance trop grande, rapproche les objets...sauf pour objet "0" qui est le leader. Correction si angle plus grand 1ue 5degres:  "&& abs(m_sinTeta) > 0.08715574"
	{
		
		

		float cosTeta = 0.9961946981, sinTeta = 0.08715574;  // correction de 5 degres de la trajectoire.

		if (m_Teta_leader < 0) // objectif a droite.  Donc rotation a droite pour rejoindre l'objectif...
		{
			sinTeta = -sinTeta;
		};

		float m_V1 = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));	//vitesse de l'objet
		m_Vx = cosTeta * temp_x - sinTeta * temp_y;
		m_Vy = sinTeta * temp_x + cosTeta * temp_y;
		m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));	//vitesse de l'objet

	

		if (m_niveau_correction > 1) m_niveau_correction = 0;
	};

	
	if (m_distance_devant < 50 && m_distance_devant >30)
	{
		
		m_niveau_correction = 1;
		float cosTeta = 0.9961946981, sinTeta = 0.08715574;				// virage 5 degres

		if (m_sinTeta > 0)												// >0: obstacle à gauche, <0: obstacle à droite.
		{
			sinTeta = -sinTeta;											// virage -5 degres.
		};

		float m_V1 = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));					//vitesse de l'objet

		m_Vx = cosTeta * temp_x - sinTeta * temp_y;						//rotation
		m_Vy = sinTeta * temp_x + cosTeta * temp_y;
		m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));						//vitesse de l'objet

		

		if (m_niveau_correction > 1) m_niveau_correction = 1;
	};



	if (m_distance_devant < 31 && m_distance_devant >20 )
	{
				
			m_niveau_correction = 2;
			float cosTeta = 0.9961946981, sinTeta = 0.08715574;				// virage 5 degres
			//float cosTeta = 0.984807, sinTeta = 0.173648;					// virage 10 degres additionnel

			if (m_sinTeta > 0)												// >0: obstacle à gauche, <0: obstacle à droite.
			{
				sinTeta = -sinTeta;											// virage -5 degres.
			};
					float m_V1 = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));			//vitesse de l'objet
						
					m_Vx = cosTeta * temp_x - sinTeta * temp_y;				//rotation
					m_Vy = sinTeta * temp_x + cosTeta * temp_y;

					m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));				//vitesse de l'objet
					
				
				if (m_niveau_correction > 2) m_niveau_correction = 2;
	};


	if (m_distance_devant < 21 && m_distance_devant >10)				 // virage additionnel
	{
				
			m_niveau_correction = 4;
			float cosTeta = 0.984807, sinTeta = 0.173648;			// virage additionnel
					//float cosTeta = 0.939693, sinTeta = 0.34202;			// virage 20 degres

			if (m_sinTeta > 0)												// >0: obstacle à gauche, <0: obstacle à droite.
			{
				sinTeta = -sinTeta;											// virage -5 degres.
			};

			float m_V1 = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));			//vitesse de l'objet

			m_Vx = cosTeta * temp_x - sinTeta * temp_y;				//rotation
			m_Vy = sinTeta * temp_x + cosTeta * temp_y;

			m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));				//vitesse de l'objet
					
				

	};

	if (m_distance_devant < 10 && m_distance_devant >3)  // virage additionnel
	{
				
			m_niveau_correction = 8;
			//float cosTeta = 0.9961946981, sinTeta = 0.08715574;  // virage 5 degres
			float cosTeta = 0.939693, sinTeta = 0.34202;  // virage 20 degres
			//float cosTeta = 0.707, sinTeta = 0.707;  // virage 45 degres
			if (m_direction == 2)
			{
				sinTeta = -sinTeta;
			};

			float m_V1 = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));			//vitesse de l'objet

			m_Vx = cosTeta * temp_x - sinTeta * temp_y;				//rotation
			m_Vy = sinTeta * temp_x + cosTeta * temp_y;

			m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));				//vitesse de l'objet
					

	};


			m_cosVitesse = m_Vx / m_V;						//calcul de l'angle de rotation de l'objet.  Utilisé pour dessiner à l'écran.
			m_sinVitesse = m_Vy / m_V;

			Rotation();
			Translation();
		
};

void CEtoile::RebonditX()
{

	// changement de vitesse et de direction
	
		m_Vx = -m_Vx; 
		
		if (abs(m_Vy) < 1) m_Vy = 2;
		
		m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));	//vitesse de l'objet 

		
}


void CEtoile::RebonditY()
{
	
		m_Vy = -m_Vy; 

		if (abs(m_Vx) < 1) m_Vx = 2;

		//if (abs(m_Vy < 1)) m_Vy = 2;

		m_V = sqrt(pow(m_Vx, 2) + pow(m_Vy, 2));	//vitesse de l'objet 
		
}
