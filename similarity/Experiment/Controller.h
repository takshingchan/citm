//
//  Controller.h
//
//  Copyright (C) 2006 Tak-Shing Chan
//

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import <QTKit/QTKit.h>

@interface Controller : NSObject {
    IBOutlet NSMenuItem			*newExperiment;
    IBOutlet NSMenuItem			*obscureNames;
    IBOutlet NSWindow			*window;
    IBOutlet NSView			*instructions;
    IBOutlet NSView			*questionnaire;
    IBOutlet NSTextField		*progressText;
    IBOutlet NSTableView		*playListView;
    IBOutlet NSMatrix			*matrix;
    IBOutlet NSProgressIndicator	*progressBar;
    IBOutlet NSView			*personal;
    IBOutlet NSPopUpButton		*age;
    IBOutlet NSPopUpButton		*sex;
    IBOutlet NSPopUpButton		*years;
    IBOutlet NSTextView			*comments;
    IBOutlet NSButton			*done;
    NSString				*directory;
    NSArray				*fileList;
    unsigned				nChoose2;
    unsigned				iteration;
    int					*order;
    struct { int first, second; }	*pairs;
    int					playList[2];
    int					playing;
    QTMovie				*movie;
    NSSound				*beep;
}

- (id) init;
- (void) dealloc;
- (void) shuffle;
- (void) updatePlayList: (unsigned) index;
- (void) awakeFromNib;
- (IBAction) beginExperiment: (id) sender;
- (IBAction) toggleObscure: (id) sender;
- (IBAction) beginQuestionnaire: (id) sender;
- (int) numberOfRowsInTableView: (NSTableView *) aTableView;
- (id) tableView: (NSTableView *) aTableView
    objectValueForTableColumn: (NSTableColumn *) aTableColumn
    row: (int) rowIndex;
- (void) eventLoop;
- (void) QTMovieDidEnd: (NSNotification *) notification;
- (void) sound: (NSSound *) sound didFinishPlaying: (BOOL) aBool;
- (void) enableMatrix: (BOOL) flag;
- (void) getRating: (id) sender;
- (IBAction) personalChanged: (id) sender;
- (IBAction) endExperiment: (id) sender;

@end
