#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

const char* img0 = "0.png";
const char* img1 = "1.png";
const char* img2 = "2.png";
const char* img3 = "3.png";
const char* img4 = "4.png";
const char* img5 = "5.png";
const char* img6 = "6.png";
const char* img7 = "7.png";
const char* img8 = "8.png";
const char* img9 = "9.png";
const char* img10 = "colon.png";

int main(int argc, char** argv) {
  SDL_Surface* s[10];
  

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();

    
    // TODO: Chargement et traitement de la texture
    s[0]=IMG_Load(img0);
    s[1]=IMG_Load(img1);
    s[2]=IMG_Load(img2);
    s[3]=IMG_Load(img3);
    s[4]=IMG_Load(img4);
    s[5]=IMG_Load(img5);
    s[6]=IMG_Load(img6);
    s[7]=IMG_Load(img7);
    s[8]=IMG_Load(img8);
    s[9]=IMG_Load(img9);
    s[10]=IMG_Load(img10);

    int i = 0;

    while (i<10){
      printf("%d\n",i);
      if (s[i] == NULL){
	printf("ERREUR CHARGEMENT IMG\n");
	return EXIT_FAILURE;
      }
      i++;
    }
    
    GLuint textureID[10];
    glGenTextures(10,&textureID[0]);

    i = 0;
    
    while (i<=10){
    //Configuration des paramètres de texture
      glBindTexture(GL_TEXTURE_2D,textureID[i]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   
    
    //Envoi des données à la carte graphique
      glTexImage2D(
		 GL_TEXTURE_2D,
		 0,
		 GL_RGB,
		 s[i]->w,
		 s[i]->h,
		 0,
		 GL_RGBA,// A changer selon format de l'image
		 GL_UNSIGNED_BYTE,
		 s[i]->pixels);

    //Détacher la texture de son point de bind
      glBindTexture(GL_TEXTURE_2D,0);
    }


    // TODO: Libération des données CPU
    i = 0;
    while (i<=10){
      SDL_FreeSurface(s[i]);
      i++;
    }



	//Boucle de dessin
	
    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // TODO: Code de dessin
	glEnable(GL_TEXTURE_2D); // activation texturing
	glBindTexture(GL_TEXTURE_2D,textureID[1]); //bind la texture à utiliser

        glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);

	//glRotatef(45,0.0,0.0,1.0);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-0.5,0.5);
	glTexCoord2f(1,0);
	glVertex2f(0.5,0.5);
	glTexCoord2f(1,1);
	glVertex2f(0.5,-0.5);
	glTexCoord2f(0,1);
	glVertex2f(-0.5,-0.5);
	glEnd();
	
	glDisable(GL_TEXTURE_2D); //desactivation sampling texture
	glBindTexture(GL_TEXTURE_2D,0); //débind texture
         

        // Fin du code de dessin

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    

    // TODO: Libération des données GPU
    i=0;
    while (i<=10){ 
      glDeleteTextures(1,&textureID[i]);
      i++;
    }

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
