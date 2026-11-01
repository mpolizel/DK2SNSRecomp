/*
 * Donkey Kong Country 2 — optional update check on start (Windows).
 *
 * When enabled (the "Check for updates on start" box beside "Skip launcher on
 * boot", saved in update.ini beside the executable), a release build asks
 * GitHub for the
 * latest release of this project and, if it is newer, offers to install it.
 * Accepting hands off to a PowerShell updater that downloads the setup pack,
 * copies it over the install without deleting anything (the pack carries no
 * build/, saves, states or settings, so those stay as they are) and reopens
 * the setup program to rebuild the game.
 */
#ifndef DKC2_UPDATE_H
#define DKC2_UPDATE_H

/* Checks, prompts and, if the player accepts, exits the process after
 * starting the updater. Returns normally otherwise. */
void Dkc2UpdateCheckOnStart(const char *current_version);

/* The launcher checkbox. Persisted immediately. */
int Dkc2UpdateGetEnabled(void);
void Dkc2UpdateSetEnabled(int enabled);

#endif
