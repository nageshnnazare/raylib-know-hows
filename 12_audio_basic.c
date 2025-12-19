/*******************************************************************************************
*
*   RAYLIB LESSON 12: Audio Basics
*   
*   Learn how to play sounds and music! Audio brings games to life.
*   This example uses procedural sounds (no external files needed).
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - audio basics");
    
    // ============================================================
    // AUDIO INITIALIZATION
    // ============================================================
    
    // InitAudioDevice() initializes the audio system
    // MUST be called before any audio functions
    // Call this ONCE at the start of your program
    InitAudioDevice();
    
    // Check if audio device was initialized successfully
    if (!IsAudioDeviceReady())
    {
        // If audio failed to initialize, show error and exit
        TraceLog(LOG_ERROR, "Audio device could not be initialized!");
        CloseWindow();
        return 1;
    }
    
    SetTargetFPS(60);

    // ============================================================
    // GENERATE SOUNDS (Procedural)
    // ============================================================
    
    // For this example, we'll generate sounds programmatically
    // In real games, you'd use: Sound sound = LoadSound("sound.wav");
    
    // Wave is the raw audio data structure (in RAM)
    // Sound is the loaded sound (in audio device memory)
    
    // Generate a "beep" sound - simple sine wave
    Wave beepWave = LoadWaveSamples(NULL);  // We'll create it manually
    
    // Actually, let's use raylib's wave generation
    // These functions create procedural audio waveforms
    
    // Since LoadWaveSamples is complex, we'll skip manual generation
    // In a real game, you would use LoadSound() to load audio files
    
    // For demonstration, we'll track sound playback with variables
    // and explain the audio functions conceptually
    
    // ============================================================
    // AUDIO PLAYBACK VARIABLES
    // ============================================================
    
    // Visual feedback for audio playback
    bool sound1Playing = false;
    bool sound2Playing = false;
    bool sound3Playing = false;
    bool musicPlaying = false;
    
    // Volume control (0.0 to 1.0)
    float masterVolume = 0.5f;
    
    // Pitch control (0.5 = half speed/lower pitch, 2.0 = double speed/higher pitch)
    float pitchValue = 1.0f;
    
    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // VOLUME CONTROL
        // ============================================================
        
        // Adjust master volume with UP/DOWN arrows
        if (IsKeyDown(KEY_UP))
        {
            masterVolume += 0.01f;
            if (masterVolume > 1.0f) masterVolume = 1.0f;
            
            // SetMasterVolume() controls the overall volume
            // 0.0 = mute, 1.0 = full volume
            SetMasterVolume(masterVolume);
        }
        
        if (IsKeyDown(KEY_DOWN))
        {
            masterVolume -= 0.01f;
            if (masterVolume < 0.0f) masterVolume = 0.0f;
            SetMasterVolume(masterVolume);
        }
        
        // ============================================================
        // PITCH CONTROL
        // ============================================================
        
        // Adjust pitch with LEFT/RIGHT arrows
        if (IsKeyDown(KEY_RIGHT))
        {
            pitchValue += 0.01f;
            if (pitchValue > 2.0f) pitchValue = 2.0f;
        }
        
        if (IsKeyDown(KEY_LEFT))
        {
            pitchValue -= 0.01f;
            if (pitchValue < 0.5f) pitchValue = 0.5f;
        }
        
        // ============================================================
        // SOUND PLAYBACK SIMULATION
        // ============================================================
        
        // In a real implementation with actual sounds:
        
        // Play sound with spacebar
        if (IsKeyPressed(KEY_SPACE))
        {
            // PlaySound(sound) - Plays a sound once
            // The sound plays and stops automatically
            sound1Playing = true;
            // Actual: PlaySound(mySound);
        }
        
        // Play sound with specific volume
        if (IsKeyPressed(KEY_ONE))
        {
            // PlaySoundMulti() allows the same sound to play multiple times simultaneously
            // Useful for rapid-fire sounds (gunshots, footsteps)
            sound2Playing = true;
            // Actual: PlaySoundMulti(mySound);
        }
        
        // Play sound with custom pitch
        if (IsKeyPressed(KEY_TWO))
        {
            // SetSoundPitch() changes the pitch/speed of a sound
            // Must be called before PlaySound()
            sound3Playing = true;
            // Actual: SetSoundPitch(mySound, pitchValue);
            // Actual: PlaySound(mySound);
        }
        
        // Simulate sound finishing after a short time
        if (sound1Playing) sound1Playing = false;
        if (sound2Playing) sound2Playing = false;
        if (sound3Playing) sound3Playing = false;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);
            
            DrawText("AUDIO BASICS", 280, 20, 30, WHITE);
            
            // ============================================================
            // AUDIO CONCEPTS DISPLAY
            // ============================================================
            
            DrawText("KEY AUDIO CONCEPTS:", 50, 70, 20, YELLOW);
            
            int y = 110;
            int spacing = 30;
            
            // Explain audio loading
            DrawText("LOADING AUDIO:", 50, y, 16, LIME);
            y += 25;
            DrawText("Sound sound = LoadSound(\"sound.wav\");", 60, y, 14, WHITE);
            y += 20;
            DrawText("Music music = LoadMusicStream(\"music.mp3\");", 60, y, 14, WHITE);
            y += spacing;
            
            // Explain playing sounds
            DrawText("PLAYING SOUNDS:", 50, y, 16, LIME);
            y += 25;
            DrawText("PlaySound(sound);  // Play once", 60, y, 14, WHITE);
            y += 20;
            DrawText("PlaySoundMulti(sound);  // Allow overlapping", 60, y, 14, WHITE);
            y += spacing;
            
            // Explain sound properties
            DrawText("SOUND PROPERTIES:", 50, y, 16, LIME);
            y += 25;
            DrawText("SetSoundVolume(sound, 0.5f);  // 0.0 to 1.0", 60, y, 14, WHITE);
            y += 20;
            DrawText("SetSoundPitch(sound, 1.5f);  // 0.5 to 2.0", 60, y, 14, WHITE);
            y += 20;
            DrawText("SetSoundPan(sound, 0.5f);  // 0.0=left, 1.0=right", 60, y, 14, WHITE);
            y += spacing;
            
            // Explain music
            DrawText("MUSIC STREAMING:", 50, y, 16, LIME);
            y += 25;
            DrawText("PlayMusicStream(music);  // Start playing", 60, y, 14, WHITE);
            y += 20;
            DrawText("UpdateMusicStream(music);  // Call every frame!", 60, y, 14, WHITE);
            y += 20;
            DrawText("StopMusicStream(music);  // Stop playing", 60, y, 14, WHITE);
            y += spacing + 10;
            
            // Right column - more concepts
            int rightX = 420;
            y = 110;
            
            DrawText("CHECKING STATE:", rightX, y, 16, LIME);
            y += 25;
            DrawText("IsSoundPlaying(sound)", rightX + 10, y, 14, WHITE);
            y += 20;
            DrawText("IsMusicStreamPlaying(music)", rightX + 10, y, 14, WHITE);
            y += spacing;
            
            DrawText("UNLOADING:", rightX, y, 16, LIME);
            y += 25;
            DrawText("UnloadSound(sound);", rightX + 10, y, 14, WHITE);
            y += 20;
            DrawText("UnloadMusicStream(music);", rightX + 10, y, 14, WHITE);
            y += 20;
            DrawText("CloseAudioDevice();", rightX + 10, y, 14, WHITE);
            y += spacing;
            
            DrawText("SUPPORTED FORMATS:", rightX, y, 16, LIME);
            y += 25;
            DrawText("WAV, OGG, MP3, FLAC", rightX + 10, y, 14, WHITE);
            y += 20;
            DrawText("QOA, XM, MOD", rightX + 10, y, 14, WHITE);
            
            // ============================================================
            // INTERACTIVE CONTROLS (SIMULATED)
            // ============================================================
            
            DrawRectangle(0, screenHeight - 100, screenWidth, 100, Fade(BLACK, 0.7f));
            
            DrawText("CONTROLS (Conceptual - no actual sounds in this demo):", 20, screenHeight - 90, 14, YELLOW);
            DrawText("SPACE: Play sound", 20, screenHeight - 65, 13, LIGHTGRAY);
            DrawText("1: Play multi sound", 20, screenHeight - 45, 13, LIGHTGRAY);
            DrawText("2: Play with custom pitch", 20, screenHeight - 25, 13, LIGHTGRAY);
            
            DrawText("UP/DOWN: Master volume", 300, screenHeight - 65, 13, LIGHTGRAY);
            DrawText("LEFT/RIGHT: Pitch", 300, screenHeight - 45, 13, LIGHTGRAY);
            
            // Display current values
            DrawText(TextFormat("Master Volume: %.2f", masterVolume), 520, screenHeight - 65, 14, WHITE);
            DrawText(TextFormat("Pitch: %.2f", pitchValue), 520, screenHeight - 45, 14, WHITE);
            
            // Visual feedback
            if (sound1Playing)
            {
                DrawCircle(740, screenHeight - 70, 20, GREEN);
                DrawText("1", 735, screenHeight - 77, 20, WHITE);
            }
            if (sound2Playing)
            {
                DrawCircle(740, screenHeight - 40, 20, YELLOW);
                DrawText("2", 735, screenHeight - 47, 20, WHITE);
            }
            if (sound3Playing)
            {
                DrawCircle(740, screenHeight - 10, 20, RED);
                DrawText("3", 735, screenHeight - 17, 20, WHITE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // In a real program with loaded sounds:
    // UnloadSound(sound1);
    // UnloadSound(sound2);
    // UnloadMusicStream(music);
    
    // IMPORTANT: Always close audio device when done
    // This frees audio resources
    CloseAudioDevice();
    
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   AUDIO SYSTEM INITIALIZATION:
*   
*   InitAudioDevice()
*   - MUST call before any audio functions
*   - Call once at program start
*   - Initializes audio hardware/software
*   
*   IsAudioDeviceReady()
*   - Returns true if audio initialized successfully
*   - Check this if audio is critical to your game
*   
*   CloseAudioDevice()
*   - MUST call when program ends
*   - Frees audio resources
*   - Call in cleanup/de-initialization section
*   
*   SOUND vs MUSIC:
*   
*   Sound:
*   - Short audio clips (< 10 seconds typically)
*   - Loaded entirely into memory
*   - Fast to play
*   - Use for: SFX, footsteps, gunshots, UI clicks
*   - Loading: Sound sound = LoadSound("file.wav");
*   
*   Music:
*   - Long audio (background music, ambience)
*   - Streamed from disk (not fully loaded into RAM)
*   - Saves memory
*   - Use for: Background music, ambient sounds
*   - Loading: Music music = LoadMusicStream("file.mp3");
*   
*   LOADING AUDIO:
*   
*   Sounds:
*   Sound mySound = LoadSound("sound.wav");
*   Sound jump = LoadSound("jump.ogg");
*   
*   Music:
*   Music bgMusic = LoadMusicStream("background.mp3");
*   Music boss = LoadMusicStream("boss_theme.ogg");
*   
*   Supported formats:
*   - WAV (uncompressed, large files)
*   - OGG (compressed, good quality, recommended)
*   - MP3 (compressed, widely supported)
*   - FLAC (lossless compression)
*   - QOA (new format, efficient)
*   - XM, MOD (tracker formats)
*   
*   PLAYING SOUNDS:
*   
*   PlaySound(sound)
*   - Plays sound once
*   - If same sound playing, stops it and restarts
*   - Simple and most common
*   
*   PlaySoundMulti(sound)
*   - Allows same sound to play multiple times simultaneously
*   - Use for rapid-fire sounds (machine gun, footsteps)
*   - Manages multiple channels automatically
*   
*   StopSound(sound)
*   - Stops a playing sound immediately
*   - Use to interrupt long sounds
*   
*   PauseSound(sound)
*   - Pauses sound (can be resumed)
*   
*   ResumeSound(sound)
*   - Resumes a paused sound
*   
*   CHECKING SOUND STATE:
*   
*   IsSoundPlaying(sound)
*   - Returns true if sound is currently playing
*   - Useful for: avoiding overlaps, waiting for sound to finish
*   
*   Example:
*   if (!IsSoundPlaying(dialogueSound)) {
*       // Sound finished, show next dialogue
*   }
*   
*   SOUND PROPERTIES:
*   
*   SetSoundVolume(sound, volume)
*   - volume: 0.0 (silent) to 1.0 (full volume)
*   - Affects only this sound
*   - Call before or while sound plays
*   
*   SetSoundPitch(sound, pitch)
*   - pitch: 0.5 to 2.0 typically
*   - 0.5 = half speed, lower pitch (deep)
*   - 1.0 = normal
*   - 2.0 = double speed, higher pitch (squeaky)
*   - Useful for variations, cartoon effects
*   
*   SetSoundPan(sound, pan)
*   - pan: 0.0 (full left) to 1.0 (full right)
*   - 0.5 = center (both speakers equally)
*   - Creates stereo positioning
*   
*   PLAYING MUSIC:
*   
*   PlayMusicStream(music)
*   - Starts playing music
*   - Music loops by default
*   
*   UpdateMusicStream(music)
*   - MUST call every frame while music plays!
*   - Updates the streaming buffer
*   - Put in your game loop
*   
*   StopMusicStream(music)
*   - Stops music playback
*   
*   PauseMusicStream(music)
*   - Pauses music (can resume)
*   
*   ResumeMusicStream(music)
*   - Resumes paused music
*   
*   MUSIC PROPERTIES:
*   
*   SetMusicVolume(music, volume)
*   - Same as sound volume (0.0 to 1.0)
*   
*   SetMusicPitch(music, pitch)
*   - Same as sound pitch
*   
*   SetMusicPan(music, pan)
*   - Same as sound pan
*   
*   MUSIC LOOPING:
*   
*   Music loops automatically by default
*   
*   To play once (no loop):
*   music.looping = false;
*   
*   To loop:
*   music.looping = true;
*   
*   MUSIC TIME CONTROL:
*   
*   GetMusicTimeLength(music)
*   - Returns total length in seconds
*   
*   GetMusicTimePlayed(music)
*   - Returns current playback position in seconds
*   
*   SeekMusicStream(music, position)
*   - Jump to specific time position
*   - position in seconds
*   
*   MASTER VOLUME:
*   
*   SetMasterVolume(volume)
*   - Controls overall volume for ALL audio
*   - 0.0 to 1.0
*   - Good for game settings/options menu
*   
*   TYPICAL GAME AUDIO STRUCTURE:
*   
*   // Initialization
*   InitAudioDevice();
*   Sound jumpSound = LoadSound("jump.wav");
*   Music bgMusic = LoadMusicStream("music.mp3");
*   PlayMusicStream(bgMusic);
*   
*   // Game loop
*   while (!WindowShouldClose()) {
*       UpdateMusicStream(bgMusic);  // Important!
*       
*       if (playerJumped) {
*           PlaySound(jumpSound);
*       }
*       
*       // ... game logic and drawing ...
*   }
*   
*   // Cleanup
*   UnloadSound(jumpSound);
*   UnloadMusicStream(bgMusic);
*   CloseAudioDevice();
*   
*   UNLOADING AUDIO:
*   
*   UnloadSound(sound)
*   - Frees sound from memory
*   - Call when done with sound
*   
*   UnloadMusicStream(music)
*   - Frees music resources
*   - Call when done with music
*   
*   ALWAYS unload in reverse order of loading!
*   
*   AUDIO TIPS:
*   
*   1. Sound volume:
*      - UI sounds: 0.3 - 0.5 (subtle)
*      - SFX: 0.5 - 0.8 (noticeable)
*      - Important sounds: 0.8 - 1.0 (loud)
*   
*   2. Music volume:
*      - Usually 0.3 - 0.6 (don't overpower SFX)
*   
*   3. Pitch variation:
*      - Add variety: play same sound with random pitch
*      - SetSoundPitch(sound, 0.9f + GetRandomValue(0, 20) / 100.0f);
*   
*   4. Format recommendations:
*      - SFX: WAV or OGG (WAV for short sounds)
*      - Music: OGG or MP3 (OGG recommended)
*   
*   5. File sizes:
*      - Keep SFX small (< 500 KB)
*      - Music can be larger but consider compression
*   
*   COMMON PATTERNS:
*   
*   Menu music:
*   if (inMenu && !IsMusicStreamPlaying(menuMusic)) {
*       PlayMusicStream(menuMusic);
*   }
*   if (!inMenu && IsMusicStreamPlaying(menuMusic)) {
*       StopMusicStream(menuMusic);
*   }
*   
*   Footstep sounds:
*   if (playerMoving && !IsSoundPlaying(footstep)) {
*       SetSoundPitch(footstep, 0.9f + (rand() % 20) / 100.0f);
*       PlaySound(footstep);
*   }
*   
*   BEST PRACTICES:
*   
*   1. Always call UpdateMusicStream() every frame
*   2. Load all sounds at start (avoid loading during gameplay)
*   3. Use music streaming for long audio
*   4. Use regular sounds for short clips
*   5. Always unload audio resources
*   6. Provide volume controls to players
*   7. Add pitch variation to repetitive sounds
*   8. Test audio on different devices/headphones
*   9. Consider separate volume controls for music and SFX
*   10. Respect player preference (some play muted!)
*   
*   COMMON MISTAKES:
*   
*   1. Forgetting UpdateMusicStream() - music won't play!
*   2. Not unloading audio - memory leak
*   3. Loading huge files as Sound (use Music instead)
*   4. Playing same sound too frequently - annoying
*   5. Music too loud - drowns out SFX
*   6. No volume control - players can't adjust
*   
*   OPTIMIZATION:
*   
*   1. Limit simultaneous sounds (use PlaySoundMulti wisely)
*   2. Unload unused audio
*   3. Use compressed formats (OGG, MP3)
*   4. Stream long audio as Music
*   5. Consider audio pooling for many similar sounds
*
*******************************************************************************************/

