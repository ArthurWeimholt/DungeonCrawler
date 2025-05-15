#include "pch.h"
#include "GameManager.h"

const std::vector<Offset> HUMAN_SHAPE = 
{
    {0,  0,  'O'},  // Head
    {1, -1, '/'},   // Left arm
    {1,  0, '|'},   // Body
    {1,  1, '\\'},  // Right arm
    {MAX_HUMAN_HEIGHT, -1, '/'},   // Left leg
    {MAX_HUMAN_HEIGHT,  1, '\\'}   // Right leg
};

const std::vector<Offset> SPIDER_SHAPE =
{
    {0, -1, '-'},
    {0,  0, '0'},
    {0,  1, '-'}
};


GameManager::GameManager()
    : m_grid(),              // Generates the grid
      m_movement(m_grid),    // Movement validation class
      m_bot_manager(),       // Creates the bot manager (Spawn and Movement)
      m_game_over(false)     
{
    // Initialize sound
    if (!m_sound.init())
    {
        endwin();
        throw std::runtime_error("Failed to initialize sound");
    }

    // Initialize bots and player
    initialize_player();
    spawn_bots(15);

    // Play game start sound
    m_sound.play(SoundEffect::GameStart);
}

GameManager::~GameManager()
{
    cleanup();
}

// Updates the bots and handles player vs monster collisions
void GameManager::update()
{
    m_bot_manager.update_bots(m_movement);
    handle_collisions();
}

void GameManager::handle_input(int ch)
{
    int dy = 0, dx = 0;

    switch (ch)
    {   
        case 'w':
        case KEY_UP:    dy = -1; break;
        case 's':
        case KEY_DOWN:  dy = 1;  break;
        case 'a':
        case KEY_LEFT:  dx = -1; break;
        case 'd':
        case KEY_RIGHT: dx = 1;  break;
        case 'p':
        case 'q':
        case 27:
            if (!pause_menu())
            {
                m_game_over = true;
            }
            else
            {
                // Draw the grid and entities
                draw();
            }
            return;
    }

    if (dy != 0 || dx != 0)
    {
        if (m_movement.can_move(m_player.y(), m_player.x(), dy, dx, m_player.get_shape()))
        {
            m_player.move(dy, dx);
            m_sound.play(SoundEffect::Footstep);
        }
        else
        {
            m_sound.play(SoundEffect::HitWall);
        }
    }
}

void GameManager::handle_collisions()
{
    for (const auto& bot : m_bot_manager.get_bots())
    {
        if (check_collision(*bot, m_player))
        {
            int damage = bot->roll_damage();
            std::cerr << "Bot damage: " << damage << std::endl;
            m_player.take_damage(damage);
            if(m_player.is_dead())
            {
                m_sound.play(SoundEffect::Death);
                m_game_over = true;
            }
            break;
        }
    }
}

void GameManager::draw()
{
    RenderGrid::draw_grid(m_grid.get_grid());
    m_player.draw();

    m_bot_manager.draw_bots();
}

void GameManager::cleanup()
{
    endwin();
    m_sound.cleanup();
}

void GameManager::initialize_player()
{
    // Pick a random room
    int room_y = rand() % MAZE_HEIGHT;
    int room_x = rand() % MAZE_WIDTH;

    // Calculate a valid position based on the random room
    int y = room_y * (ROOM_HEIGHT + WALL) + WALL;
    int x = room_x * (ROOM_WIDTH + WALL) + WALL + 1;

    // Spawn and draw the player in the random room
    m_player = Player(y, x, HUMAN_SHAPE, CYAN);
    m_player.draw();
}

// Number of bots and msec time before bot is allowed to move
void GameManager::spawn_bots(int count, BotAttributes bot_attr)
{
    // Spawns and draws the bots
    for (int i = 0; i < count; ++i)
    {
        // Pick a random room
        int room_y = rand() % MAZE_HEIGHT;
        int room_x = rand() % MAZE_WIDTH;

        // Calculate a valid position based on the random room
        int y = room_y * (ROOM_HEIGHT + WALL) + WALL;
        int x = room_x * (ROOM_WIDTH + WALL) + WALL + 1;
        m_bot_manager.spawn_bot(y, x, SPIDER_SHAPE, bot_attr);
    }
}

bool GameManager::check_collision(const Entity& a, const Entity& b) const
{
    for (const auto& pa : a.get_shape())
    {
        int ay = a.y() + pa.dy;
        int ax = a.x() + pa.dx;

        for (const auto& pb : b.get_shape())
        {
            int by = b.y() + pb.dy;
            int bx = b.x() + pb.dx;

            if (ay == by && ax == bx)
                return true;
        }
    }
    return false;
}

bool GameManager::pause_menu()
{
    // Handle the pause menu logic and use Renderer to display it
    int choice = 0;
    int key;

    while (true)
    {
        RenderGrid::draw_pause_menu(choice);

        key = getch();
        switch (key)
        {
            case KEY_UP:
            case 'w': case 'W':
                choice = (choice - 1 + 2) % 2;
                break;
            case KEY_DOWN:
            case 's': case 'S':
                choice = (choice + 1) % 2;
                break;
            case '\n':
            case KEY_ENTER:
                if (choice == 0) // Resume
                {
                    // Clear the screen before returning to the game
                    clear();
                    return true;  // Resume the game
                }
                else // Quit
                {
                    return false;  // Exit the game
                }
        }
    }
}
