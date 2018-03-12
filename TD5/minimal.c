#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static unsigned int WINDOW_WIDTH = 600;
static unsigned int WINDOW_HEIGHT = 600;


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*fonctions*/
void drawSquare();
void drawLandmark();
void drawCircle();
void drawClock();

void resize(int width , int height ){
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1.,-1.,1.);
  SDL_SetVideoMode(width,height,BIT_PER_PIXEL,SDL_OPENGL|SDL_RESIZABLE);
}

void rescale(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScalef(0.125,0.125,0.125);
}
  

 
int main(int argc, char** argv) {



    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("HORLOGE", NULL);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Boucle d'affichage */
    rescale();
    int loop = 1;

            
        /* Placer ici le code de dessin */
    glColor3ub(150,100,0);
    drawClock();

	
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();


		   /* Echange du front et du back buffer : mise à jour de la fenêtre */
	// SDL_GL_SwapBuffers();
    
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
	  

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
		  
		 
                    break;


	        /* Redimentionnement fenêtre */
	        
	        case SDL_VIDEORESIZE:
		  WINDOW_WIDTH = e.resize.w;
		  WINDOW_HEIGHT = e.resize.h;
		  resize(WINDOW_WIDTH,WINDOW_HEIGHT);
     
		  
		  break;
	      
	      
	     
                /* Touche clavier */
                case SDL_KEYDOWN:
                	break;
	
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
	   /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}






void drawSquare(){
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glBegin(GL_LINES);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,0.5);
  glEnd();
}

void drawLandmark(){
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glColor3ub(255,0,0);
  glBegin(GL_LINES);
  glVertex2f(-0.5,0);
  glVertex2f(0.5,0);
  glEnd();
  glColor3ub(0,255,0);
  glBegin(GL_LINES);
  glVertex2f(0,0.5);
  glVertex2f(0,-0.5);
  glEnd();
}


void drawCircle(){
	
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
 glBegin(GL_POLYGON);
 for(int i=0;i<1000;++i)
  {
  glVertex2f(cos(2*3.14159*i/1000.0)*0.5,sin(2*3.14159*i/1000.0)*0.5);
  }
 glEnd();
}

	
void drawClockLine(){
	int i = 0;
	glPushMatrix();
	while (i<12){
		glRotatef(30,0,0,1);
		glBegin(GL_LINES);
			glVertex2f(6,0);
			glVertex2f(7,0);
		glEnd();
		i++;
	}
	glPopMatrix();
}

void drawBigHand(){
	glColor3ub(0,0,0);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(0.2,0);
		glVertex2f(0.2,0);
		glVertex2f(0.2,7);
		glVertex2f(0.2,7);
		glVertex2f(0,7);
		glVertex2f(0,7);
		glVertex2f(0,0);
	glEnd();

}

void drawSecondHand(){
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(3,6);
	glEnd();
}

void drawClock(){

	glColor3ub(255,255,255);
	glPushMatrix();
		glScalef(15,15,0);
		drawCircle();
	glPopMatrix();
	glColor3ub(0,0,0);
	
	drawClockLine();
	drawBigHand();
	drawSecondHand();

	glPushMatrix();
		glColor3ub(0,0,0);
		glScalef(0.5,0.5,0);
		drawCircle();
	glPopMatrix();

}
  
  
