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
    unsigned				n;
    unsigned				iteration;
    int					*order;
    int					playIndex;
    BOOL				playing;
    QTMovie				*movie;
}

- (id) init;
- (void) dealloc;
- (void) shuffle;
- (void) awakeFromNib;
- (IBAction) beginExperiment: (id) sender;
- (IBAction) beginQuestionnaire: (id) sender;
- (int) numberOfRowsInTableView: (NSTableView *) aTableView;
- (id) tableView: (NSTableView *) aTableView
    objectValueForTableColumn: (NSTableColumn *) aTableColumn
    row: (int) rowIndex;
- (void) eventLoop;
- (void) QTMovieDidEnd: (NSNotification *) notification;
- (void) enableMatrix: (BOOL) flag;
- (void) getRating: (id) sender;
- (IBAction) personalChanged: (id) sender;
- (IBAction) endExperiment: (id) sender;

@end
