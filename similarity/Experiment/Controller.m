//
//  Controller.m
//
//  Copyright (C) 2006 Tak-Shing Chan
//

#import <stdio.h>
#import <stdlib.h>
#import "Controller.h"

// Number of practice trials
#define PRACT	3

// Total number of trials (including practice trials)
#define TRIALS	78

@implementation Controller

- (id) init
{
    unsigned		i, j, k, n;

    if ((self = [super init])) {

	// Read the experimental stimuli directory
	directory = [[[NSHomeDirectory()
	    stringByAppendingPathComponent: @"Music"]
	    stringByAppendingPathComponent: @"Similarity"]
	    retain];
	if ((fileList = [[[NSFileManager defaultManager]
	    directoryContentsAtPath: directory] retain])) {

	    // Calculate number-of-files choose two
	    n = [fileList count];
	    nChoose2 = n * (n - 1) / 2;
	    iteration = 0;
	    order = malloc(nChoose2 * sizeof *order);
	    pairs = malloc(nChoose2 * sizeof *pairs);
	}
	if (!fileList || nChoose2 < TRIALS || !order || !pairs) {
	    NSLog(@"Failed to initialise controller");
	    [self dealloc];
	    return nil;
	}

	// Generate all combinations of pairs
	for (i = k = 0; i < n - 1; i++) {
	    for (j = i + 1; j < n; j++) {
		order[k] = k;
		pairs[k].first = i;
		pairs[k++].second = j;
	    }
	}

	// Shuffle the list
	srandom([NSDate timeIntervalSinceReferenceDate]);
	[self shuffle];
	[self updatePlayList: 0];
	playing = -1;

	// Initialise movie and beep
	movie = nil;
	[[NSNotificationCenter defaultCenter] addObserver: self
	    selector: @selector(QTMovieDidEnd:)
	    name: QTMovieDidEndNotification object: nil];
	beep = [[NSSound soundNamed: @"Tink"] retain];
	[beep setDelegate: self];
    }
    return self;
}

- (void) dealloc
{
    [beep release];
    [[NSNotificationCenter defaultCenter] removeObserver: self];
    if (movie)
	[movie release];
    free(order);
    free(pairs);
    [fileList release];
    [directory release];
    [super dealloc];
}

- (void) shuffle
{
    unsigned		i, j, k;

    // Fisher-Yates shuffle
    for (i = nChoose2 - 1; i > 0; i--)  {
	j = random() % (i + 1);
	k = order[i];
	order[i] = order[j];
	order[j] = k;
    }
}

- (void) updatePlayList: (unsigned) index
{
    if (random() % 2) {
	playList[0] = pairs[order[index]].first;
	playList[1] = pairs[order[index]].second;
    } else {
	playList[0] = pairs[order[index]].second;
	playList[1] = pairs[order[index]].first;
    }
}

- (void) awakeFromNib
{
    // Relying on the fact that ANSI C closes all open streams on
    // exit
    while (!freopen([[NSHomeDirectory()
	stringByAppendingPathComponent: @".Similarity"]
	UTF8String], "a", stderr))
	NSRunAlertPanel(@"Cannot open ~/.Similarity",
	    @"Please ask Tak-Shing Chan to fix this before continuing this application.",
	    @"Continue", nil, nil);
    [progressBar setMaxValue: TRIALS];
}

- (IBAction) beginExperiment: (id) sender
{
    [newExperiment setEnabled: NO];
    [obscureNames setEnabled: NO];
    NSLog(@"----------------");
    NSLog(([obscureNames state] == NSOffState) ?
	@" New Experiment " : @" Obscured Names ");
    NSLog(@"----------------");
    SetSystemUIMode(kUIModeAllHidden, kUIOptionAutoShowMenuBar);
    [window setContentView: instructions];
    [window makeKeyAndOrderFront: nil];
}

- (IBAction) toggleObscure: (id) sender
{
    [sender setState: ([sender state] == NSOffState) ? NSOnState
	: NSOffState];
}

- (IBAction) beginQuestionnaire: (id) sender
{
    [window setContentView: questionnaire];
    [self eventLoop];
}

- (int) numberOfRowsInTableView: (NSTableView *) aTableView
{
    return 2;
}

- (id) tableView: (NSTableView *) aTableView
    objectValueForTableColumn: (NSTableColumn *) aTableColumn
    row: (int) rowIndex
{
    if ([[aTableColumn identifier] isEqualToString: @"playing"])
	return (rowIndex == playing) ? [NSString
	    stringWithUTF8String: "\357\243\277"] : @"";
    else
	return ([obscureNames state] == NSOffState) ? [fileList
	    objectAtIndex: playList[rowIndex]] : [NSString
	    stringWithFormat: @"Excerpt No. %d",
	    playList[rowIndex] + 1];
}

- (void) eventLoop
{
    NSString		*path;

    if (iteration >= TRIALS * 4) {
	[window setContentView: personal];
	return;
    }
    switch (iteration % 4) {
    case 0: // Play the first piece
	    if (iteration / 4 < PRACT) {
		[progressText setStringValue: [NSString
		    stringWithFormat: @"Practice %d of %d",
		    iteration / 4 + 1, PRACT]];
	    } else {
		[progressText setStringValue: [NSString
		    stringWithFormat: @"Trial %d of %d", 
		    iteration / 4 - PRACT + 1, TRIALS - PRACT]];
	    }
	    [progressBar setDoubleValue: iteration / 4];
	    [self updatePlayList: iteration / 4];
	    playing = 0;
	    [playListView reloadData];
	    path = [fileList objectAtIndex: playList[playing]];
	    if (iteration / 4 >= PRACT)
		NSLog(@"%@", path);
	    if (movie)
		[movie release];
	    movie = [[QTMovie movieWithFile: [directory
		stringByAppendingPathComponent: path] error: nil]
		retain];
	    [movie play];
	    break;
    case 1: // Play the beep sound
	    [beep performSelector: @selector(play) withObject:
		nil afterDelay: 0.6];
	    break;
    case 2: // Play the second piece
	    playing = 1;
	    [playListView reloadData];
	    path = [fileList objectAtIndex: playList[playing]];
	    if (iteration / 4 >= PRACT)
		NSLog(@"%@", path);
	    if (movie)
		[movie release];
	    movie = [[QTMovie movieWithFile: [directory
		stringByAppendingPathComponent: path] error: nil]
		retain];
	    [movie performSelector: @selector(play) withObject:
		nil afterDelay: 0.6];
	    break;
    case 3: // Enable the questionnaire
	    playing = -1;
	    [playListView reloadData];
	    [self enableMatrix: YES];
    }
    iteration++;
}

- (void) QTMovieDidEnd: (NSNotification *) notification
{
    [self eventLoop];
}

- (void) sound: (NSSound *) sound didFinishPlaying: (BOOL) aBool
{
    [self eventLoop];
}

- (void) enableMatrix: (BOOL) flag
{
    NSEnumerator	*enumerator = [[matrix cells]
	objectEnumerator];
    NSCell		*cell;

    while ((cell = [enumerator nextObject])) {
	[cell setEnabled: flag];
	[cell setHighlighted: NO];
    }
}

- (void) getRating: (id) sender
{
    [self enableMatrix: NO];

    // We are one iteration behind
    if (iteration / 4 > PRACT)
	NSLog(@"(%d)", [[sender selectedCell] tag]);
    [self eventLoop];
}

- (IBAction) personalChanged: (id) sender
{
    [done setEnabled: YES];
}

- (IBAction) endExperiment: (id) sender
{
    NSLog(@"----------------");
    NSLog(@"    Personal    ");
    NSLog(@"----------------");
    NSLog(@"Age: %@", [age titleOfSelectedItem]);
    NSLog(@"Sex: %@", [sex titleOfSelectedItem]);
    NSLog(@"Years: %@", [years titleOfSelectedItem]);
    NSLog(@"Comments: %@", [comments string]);
    [window orderOut: nil];

    // Reset everything to initial values
    [progressText setStringValue: @""];
    [progressBar setDoubleValue: 0];
    [age selectItemAtIndex: 0];
    [sex selectItemAtIndex: 0];
    [years selectItemAtIndex: 0];
    [comments setString: @""];
    [done setEnabled: NO];
    iteration = 0;
    [self shuffle];
    [self updatePlayList: 0];
    SetSystemUIMode(kUIModeNormal, 0);
    [obscureNames setEnabled: YES];
    [newExperiment setEnabled: YES];
}

@end
