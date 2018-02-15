#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/*EXERCICE 5*/

static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resize(int width , int height ){
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,1.,-1.,1.);
  SDL_SetVideoMode(width,height,BIT_PER_PIXEL,SDL_OPENGL|SDL_RESIZABLE);
}


void drawpoint(int x,int y){

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glColor3ub(255,0,0);
  glBegin(GL_POINTS);
  glVertex2f(-1+2.*x/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT));
  glEnd();
}


void drawline(int x,int y){
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glColor3ub(255,0,0);
  glBegin(GL_LINES);
  glVertex2f(-1+2.*x/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT));
  glVertex2f(-1+2.*(x+10)/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT));
  glEnd();
}


void drawtriangle(int x,int y){
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);
  glColor3ub(255,0,0);
  glBegin(GL_TRIANGLES);
  glVertex2f(-1+2.*x/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT));
  glVertex2f(-1+2.*(x+10)/WINDOW_WIDTH,-(-1+2.*(y+10)/WINDOW_HEIGHT));
  glVertex2f(-1+2.*(x-10)/WINDOW_WIDTH,-(-1+2.*(y+10)/WINDOW_HEIGHT));
  glEnd();
}

void draw(int x,int y,int key){
 
  if (key == 112){
    drawpoint(x,y);
  }
  if (key == 108){
    drawline(x,y);
  }
  if (key == 116){
    drawtriangle(x,y);
  }
}

void drawColor(){
  glColor3ub(255,0,0);
  glRectf(-1.,1.,-0.5,-1.);
  glColor3ub(0,255,0);
  glRectf(-0.5,1.,0,-1.);
  glColor3ub(0,0,255);
  glRectf(0,1.,0.5,-1.);
  glColor3ub(255,255,255);
  glRectf(0.5,1.,1,-1);
}
 
int main(int argc, char** argv) {
  
  float R=0;
  float V=0;
  float B=0;

  int key=112;

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
    SDL_WM_SetCaption("CHANGEMENT DU TITRE :D", NULL);
   
    /* Boucle d'affichage */
    int loop = 1;
    int mode = 0;
    
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
      
	glClearColor(R/255,V/255,B,1);
	
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
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
		  
		    draw(e.button.x,e.button.y,key);
		   
                    break;

		/* Déplacement souris */
	        case SDL_MOUSEMOTION:	    
                    break;

	        /* Redimentionnement fenêtre */
	        
	        case SDL_VIDEORESIZE:
		  WINDOW_WIDTH = e.resize.w;
		  WINDOW_HEIGHT = e.resize.h;
		  resize(WINDOW_WIDTH,WINDOW_HEIGHT);  
		  break;
	      
	      
	     
                /* Touche clavier */
                case SDL_KEYDOWN:
		  /*Touche q pour quitter*/
		  key = e.key.keysym.sym;
		  if (e.key.keysym.sym == 113){
		    loop = 0;
		    break;
		  }
		   if (e.key.keysym.sym == SDLK_SPACE){
		     drawColor();
		     break;
		  }
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    break;

                default:
                    break;
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
