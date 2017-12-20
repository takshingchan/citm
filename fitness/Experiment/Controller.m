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
#define TRIALS	178

@implementation Controller

- (id) init
{
    unsigned		i;

    if ((self = [super init])) {

	// Read the experimental stimuli directory
	directory = [[[NSHomeDirectory()
	    stringByAppendingPathComponent: @"Music"]
	    stringByAppendingPathComponent: @"Liking"]
	    retain];
	if ((fileList = [[[NSFileManager defaultManager]
	    directoryContentsAtPath: directory] retain])) {
	    n = [fileList count];
	    iteration = 0;
	    order = malloc(n * sizeof *order);
	}
	if (!fileList || n < TRIALS || !order) {
	    NSLog(@"Failed to initialise controller");
	    [self dealloc];
	    return nil;
	}
	for (i = 0; i < n; i++)
	    order[i] = i;

	// Shuffle the list
	srandom([NSDate timeIntervalSinceReferenceDate]);
	[self shuffle];
	playIndex = 0;
	playing = NO;

	// Initialise movie
	movie = nil;
	[[NSNotificationCenter defaultCenter] addObserver: self
	    selector: @selector(QTMovieDidEnd:)
	    name: QTMovieDidEndNotification object: nil];
    }
    return self;
}

- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver: self];
    if (movie)
	[movie release];
    free(order);
    [fileList release];
    [directory release];
    [super dealloc];
}

- (void) shuffle
{
    unsigned		i, j, k;

    // Fisher-Yates shuffle
    for (i = n - 1; i > 0; i--)  {
	j = random() % (i + 1);
	k = order[i];
	order[i] = order[j];
	order[j] = k;
    }
}

- (void) awakeFromNib
{
    // Relying on the fact that ANSI C closes all open streams on
    // exit
    while (!freopen([[NSHomeDirectory()
	stringByAppendingPathComponent: @".Liking"]
	UTF8String], "a", stderr))
	NSRunAlertPanel(@"Cannot open ~/.Liking",
	    @"Please ask Tak-Shing Chan to fix this before continuing this application.",
	    @"Continue", nil, nil);
    [progressBar setMaxValue: TRIALS];
}

- (IBAction) beginExperiment: (id) sender
{
    [newExperiment setEnabled: NO];
    NSLog(@"----------------");
    NSLog(@" New Experiment ");
    NSLog(@"----------------");
    SetSystemUIMode(kUIModeAllHidden, kUIOptionAutoShowMenuBar);
    [window setContentView: instructions];
    [window makeKeyAndOrderFront: nil];
}

- (IBAction) beginQuestionnaire: (id) sender
{
    [window setContentView: questionnaire];
    [self eventLoop];
}

- (int) numberOfRowsInTableView: (NSTableView *) aTableView
{
    return 1;
}

- (id) tableView: (NSTableView *) aTableView
    objectValueForTableColumn: (NSTableColumn *) aTableColumn
    row: (int) rowIndex
{
    if ([[aTableColumn identifier] isEqualToString: @"playing"])
	return playing ? [NSString stringWithUTF8String:
	    "\357\243\277"] : @"";
    else
	return [NSString stringWithFormat: @"Excerpt No. %d",
	    order[playIndex] + 1];
}

- (void) eventLoop
{
    NSString		*path;

    if (iteration >= TRIALS * 2) {
	[window setContentView: personal];
	return;
    }
    switch (iteration % 2) {
    case 0: // Play the first piece
	    playIndex = iteration / 2;
	    if (playIndex < PRACT) {
		[progressText setStringValue: [NSString
		    stringWithFormat: @"Practice %d of %d",
		    playIndex + 1, PRACT]];
	    } else {
		[progressText setStringValue: [NSString
		    stringWithFormat: @"Trial %d of %d", 
		    playIndex - PRACT + 1, TRIALS - PRACT]];
	    }
	    [progressBar setDoubleValue: playIndex];
	    playing = YES;
	    [playListView reloadData];
	    path = [fileList objectAtIndex: order[playIndex]];
	    if (playIndex >= PRACT)
		NSLog(@"%@", path);
	    if (movie)
		[movie release];
	    movie = [[QTMovie movieWithFile: [directory
		stringByAppendingPathComponent: path] error: nil]
		retain];
	    [movie play];
	    break;
    case 1: // Enable the questionnaire
	    playing = NO;
	    [playListView reloadData];
	    [self enableMatrix: YES];
    }
    iteration++;
}

- (void) QTMovieDidEnd: (NSNotification *) notification
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
    if (playIndex >= PRACT)
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
    playIndex = 0;
    SetSystemUIMode(kUIModeNormal, 0);
    [newExperiment setEnabled: YES];
}

@end
