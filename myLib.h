#define MODE3 3
#define BG2_ENABLE (1<<10)
#define REG_DISPCTL *(unsigned short*) 0x4000000

#define OFFSET(r, c, w) ((r) *w + (c))

#define COLOR(r,g,b) ((r)| ((g) << 5) | ((b) << 10))
#define WHITE COLOR(31,31,31)
#define BLACK COLOR (0,0,0)
#define GREEN COLOR (0,31,0)
#define RED COLOR(31,0,0)
#define BLUE COLOR(0,0,31)

#define u16 unsigned short
#define u32 unsigned int

#define True 1
#define False 0

#define SCANLINECOUNTER *(volatile unsigned short*) 0x4000006

// *** Input =========================================================

// Buttons
#define KEY_MASK 0x03FF
#define BUTTON_ADDRESS (*((unsigned short *) 0x4000130))
#define BUTTON_HELD(key) (~BUTTON_ADDRESS & (key))

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

void key_poll();
u32 key_curr_state();
u32 key_prev_state();
u32 key_is_down(u32 key);
u32 key_is_up(u32 key);
u32 key_was_down(u32 key);
u32 key_was_up(u32 key);
u32 key_held(u32 key);
u32 key_hit(u32 key);
u32 key_released(u32 key);
extern unsigned short *videoBuffer;

void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int width, int height, unsigned short color);
void waitForVBlank();


//AI RELATED STUFF HERE!!!!
#define NPC_COUNT 10

enum races {GIANT, PYGMY};
enum AI_states {IDLE, ATTRACT, REPEL};

typedef struct {
    int row;
    int col;
    int size;
    int race;
    int ai_state;
    
    int alive;//unused, could be used to not draw dead NPCs
    
    int col_momentum;
    int row_momentum;
} NPC;

typedef struct {
    int row;
    int col;
    int size;
} PLAYER;