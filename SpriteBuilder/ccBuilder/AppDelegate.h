/*
 * CocosBuilder: http://www.cocosbuilder.com
 *
 * Copyright (c) 2011 Viktor Lidholt
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#import "cocos2d.h"
#import "PSMTabBarControl.h"
#import "SMTabBar.h"

#define kCCBNumCanvasDevices 12

enum {
    kCCBCanvasSizeCustom = 0,
    kCCBCanvasSizeIPhoneLandscape,
    kCCBCanvasSizeIPhonePortrait,
    kCCBCanvasSizeIPhone5Landscape,
    kCCBCanvasSizeIPhone5Portrait,
    kCCBCanvasSizeIPadLandscape,
    kCCBCanvasSizeIPadPortrait,
    kCCBCanvasSizeAndroidXSmallLandscape,
    kCCBCanvasSizeAndroidXSmallPortrait,
    kCCBCanvasSizeAndroidSmallLandscape,
    kCCBCanvasSizeAndroidSmallPortrait,
    kCCBCanvasSizeAndroidMediumLandscape,
    kCCBCanvasSizeAndroidMediumPortrait,
};

enum {
    kCCBBorderDevice = 0,
    kCCBBorderTransparent,
    kCCBBorderOpaque,
    kCCBBorderNone
};

enum {
    kCCBAlignHorizontalCenter,
    kCCBAlignVerticalCenter,
    kCCBAlignLeft,
    kCCBAlignRight,
    kCCBAlignTop,
    kCCBAlignBottom,
    kCCBAlignAcross,
    kCCBAlignDown,
    kCCBAlignSameWidth,
    kCCBAlignSameHeight,
    kCCBAlignSameSize,
};

enum {
    kCCBArrangeBringToFront,
    kCCBArrangeBringForward,
    kCCBArrangeSendBackward,
    kCCBArrangeSendToBack,
};

enum {
    kCCBDocDimensionsTypeFullScreen,
    kCCBDocDimensionsTypeNode,
    kCCBDocDimensionsTypeLayer,
};


@class CCBDocument;
@class ProjectSettings;
@class CCBHTTPServer;
@class AssetsWindowController;
@class PlugInManager;
@class ResourceManager;
@class ResourceManagerPanel;
@class ResourceManagerOutlineHandler;
@class CCBGLView;
@class CCBTransparentWindow;
@class CCBTransparentView;
@class TaskStatusWindow;
@class CCBPublisher;
@class CCBWarnings;
@class SequencerHandler;
@class SequencerScrubberSelectionView;
@class MainWindow;
@class PlayerConsoleWindow;
@class HelpWindow;
@class APIDocsWindow;
@class MainToolbarDelegate;
@class PlayerConnection;
@class CCBSplitHorizontalView;
@class AboutWindow;
@class ResourceManagerPreviewView;
@class SMTabBar;
@class ResourceManagerTilelessEditorManager;
@class CCBImageBrowserView;
@class PlugInNodeViewHandler;
@class PropertyInspectorHandler;
@class LocalizationEditorHandler;
@class PhysicsHandler;

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate, SMTabBarDelegate>
{
    
    // Panel Views
    IBOutlet NSView* leftPanel;
    IBOutlet NSView* rightPanel;
    IBOutlet NSSegmentedControl *panelVisibilityControl;
    
    // Cocos2D view
    IBOutlet CCBGLView* cocosView;
    IBOutlet NSView* mainView;
    IBOutlet CCBSplitHorizontalView* splitHorizontalView;
    
    // Inspector views
    IBOutlet PropertyInspectorHandler* propertyInspectorHandler;
    
    IBOutlet NSScrollView* inspectorScroll;
    NSView* inspectorDocumentView;
    NSMutableDictionary* currentInspectorValues;
    
    IBOutlet NSScrollView* inspectorCodeScroll;
    NSView* inspectorCodeDocumentView;
    
    IBOutlet NSToolbar* toolbar;
    MainToolbarDelegate* toolbarDelegate;
    
    // Tabs
    IBOutlet PSMTabBarControl* tabBar;
    NSTabView* tabView;
    
    // Inspector componentes
    // IBOutlet NSComboBox* inspectorSpriteName;
    // IBOutlet NSTextView* inspectorLabelBMFontString;
    BOOL canEditContentSize;
    BOOL canEditCustomClass;
    
    BOOL lockedScaleRatio;
    
    // Inspector tab bars
    IBOutlet SMTabBar* projectViewTabs;
    IBOutlet NSTabView* projectTabView;
    
    IBOutlet SMTabBar* itemViewTabs;
    IBOutlet NSTabView* itemTabView;
    
    // Outline view heirarchy
    SequencerHandler* sequenceHandler;
    IBOutlet NSOutlineView* outlineHierarchy;
    IBOutlet SequencerScrubberSelectionView* scrubberSelectionView;
    IBOutlet NSTextField* timeDisplay;
    IBOutlet NSSlider* timeScaleSlider;
    IBOutlet NSScroller* timelineScroller;
    IBOutlet NSScrollView* sequenceScrollView;
    
    // Selections
    NSMutableArray* loadedSelectedNodes;
    NSMutableArray* selectedNodes;
    
    // Menus
    IBOutlet NSMenu* menuCanvasSize;
    IBOutlet NSMenu* menuCanvasBorder;
    IBOutlet NSMenu* menuResolution;
    IBOutlet NSMenu* menuContextKeyframe;
    IBOutlet NSMenu* menuContextKeyframeInterpol;
    IBOutlet NSMenu* menuContextResManager;
    IBOutlet NSMenu *menuContextKeyframeNoselection;
    
    IBOutlet NSPopUpButton* menuTimelinePopup;
    IBOutlet NSMenu* menuTimeline;
    IBOutlet NSTextField* lblTimeline;
    
    IBOutlet NSPopUpButton* menuTimelineChainedPopup;
    IBOutlet NSMenu* menuTimelineChained;
    IBOutlet NSTextField* lblTimelineChained;

    CGSize defaultCanvasSizes[kCCBNumCanvasDevices+1];
    // IBOutlet NSMenuItem* menuItemStageCentered;
    BOOL defaultCanvasSize;
    
    // IBOutlet NSMenuItem* menuItemJSControlled;
    // IBOutlet NSMenuItem* menuItemSafari;
    // IBOutlet NSMenuItem* menuItemChrome;
    // IBOutlet NSMenuItem* menuItemFirefox;
    
    IBOutlet NSSegmentedControl* segmPublishBtn;
    
    // Resource manager
    ResourceManager* resManager;
    IBOutlet NSView* previewViewContainer;
    NSView* previewViewImage;
    NSView* previewViewGeneric;
    ResourceManagerPreviewView* previewViewOwner;
    IBOutlet NSSplitView* resourceManagerSplitView;
    
    // Tileless editor view
    ResourceManagerTilelessEditorManager* tilelessEditorManager;
    IBOutlet CCBImageBrowserView* projectImageBrowserView;
    IBOutlet NSTableView* tilelessEditorTableFilterView;
    IBOutlet NSSplitView* tilelessEditorSplitView;
    
    // PlugIn manager view
    PlugInNodeViewHandler* plugInNodeViewHandler;
    IBOutlet NSCollectionView* plugInNodeCollectionView;
    
    // Project
    ProjectSettings* projectSettings;
    
    // Project display
    IBOutlet NSOutlineView* outlineProject;
    ResourceManagerOutlineHandler* projectOutlineHandler;
    
    // Documents
    NSMutableArray* delayOpenFiles;
    CCBDocument* currentDocument;
    BOOL hasOpenedDocument;
    
    // PlugIns (nodes)
    PlugInManager* plugInManager;
    
    // Guides
    BOOL showGuides;
    BOOL snapToGuides;
    
    // Sticky notes
    BOOL showStickyNotes;
    
    // Transparent window for components on top of cocos scene
    CCBTransparentWindow* guiWindow;
    CCBTransparentView* guiView;
    
    // Warnings
    NSString* errorDescription;
    
    // Modal status window
    TaskStatusWindow* modalTaskStatusWindow;
    
    // Player
    PlayerConnection* connection;
    PlayerConsoleWindow* playerConsoleWindow;
    
    // Help window
    HelpWindow* helpWindow;
    APIDocsWindow* apiDocsWindow;
    
    // About window
    AboutWindow* aboutWindow;
    
    // Animation playback
    BOOL playingBack;
    double playbackLastFrameTime;
    
    // JavaScript bindings
    BOOL jsControlled;
    
    // Localization editor
    IBOutlet LocalizationEditorHandler* localizationEditorHandler;
    
    // Physics editor
    IBOutlet PhysicsHandler* physicsHandler;
    
@private
    MainWindow *window;
    
}

@property (assign) IBOutlet MainWindow *window;

@property (nonatomic,readonly) IBOutlet NSOutlineView* outlineProject;


@property (nonatomic,readonly) ResourceManager* resManager;
@property (nonatomic,readonly) ResourceManagerOutlineHandler* projectOutlineHandler;
@property (nonatomic,retain) CCBDocument* currentDocument;
@property (nonatomic,assign) BOOL hasOpenedDocument;
@property (nonatomic,readonly) CCBGLView* cocosView;

@property (nonatomic,retain) IBOutlet PropertyInspectorHandler* propertyInspectorHandler;

@property (nonatomic,assign) BOOL canEditContentSize;
@property (nonatomic,assign) BOOL defaultCanvasSize;
@property (nonatomic,assign) BOOL canEditCustomClass;
@property (nonatomic,assign) BOOL canEditStageSize;

@property (nonatomic,readonly) CCNode* selectedNode;

@property (nonatomic,retain) NSArray* selectedNodes;
@property (nonatomic,readonly) NSMutableArray* loadedSelectedNodes;

@property (nonatomic,assign) BOOL showGuides;
@property (nonatomic,assign) BOOL snapToGuides;
@property (nonatomic,assign) BOOL showStickyNotes;

@property (nonatomic,readonly) CCBTransparentView* guiView;
@property (nonatomic,readonly) CCBTransparentWindow* guiWindow;

@property (nonatomic,readonly) IBOutlet NSMenu* menuContextKeyframe;
@property (nonatomic,readonly) IBOutlet NSMenu* menuContextKeyframeInterpol;
@property (nonatomic,readonly) IBOutlet NSMenu* menuContextResManager;
@property (nonatomic,readonly) IBOutlet NSMenu *menuContextKeyframeNoselection;
@property (nonatomic,readonly) NSSegmentedControl *panelVisibilityControl;

@property (nonatomic,retain) ProjectSettings* projectSettings;
@property (nonatomic,readonly) PlayerConnection* connection;

@property (nonatomic,copy) NSString* errorDescription;

// Transparent window
- (void) resizeGUIWindow:(NSSize)size;

// PlugIns and properties
@property (nonatomic,readonly) PlugInManager* plugInManager;
- (void) refreshProperty:(NSString*) name;
- (void) refreshPropertiesOfType:(NSString*)type;

@property (nonatomic,readonly) IBOutlet LocalizationEditorHandler* localizationEditorHandler;

// Physics
@property (nonatomic,readonly) PhysicsHandler* physicsHandler;
@property (nonatomic,readonly) NSTabView* itemTabView;


// Methods
+ (AppDelegate*) appDelegate;

- (void) updateTimelineMenu;
- (void) updateInspectorFromSelection;
- (void) switchToDocument:(CCBDocument*) document;
- (void) closeLastDocument;
- (void) openFile:(NSString*) fileName;
- (void) openJSFile:(NSString*) fileName;
- (void) openJSFile:(NSString*) fileName highlightLine:(int)line;
- (void) resetJSFilesLineHighlight;

// Menu options
- (void) dropAddSpriteNamed:(NSString*)spriteFile inSpriteSheet:(NSString*)spriteSheetFile at:(CGPoint)pt parent:(CCNode*)parent;
- (void) dropAddSpriteNamed:(NSString*)spriteFile inSpriteSheet:(NSString*)spriteSheetFile at:(CGPoint)pt;
- (void) dropAddCCBFileNamed:(NSString*)ccbFile at:(CGPoint)pt parent:(CCNode*)parent;

- (IBAction)menuTimelineSettings:(id)sender;

- (IBAction) menuNudgeObject:(id)sender;
- (IBAction) menuMoveObject:(id)sender;

- (IBAction) menuSelectBehind:(id)sender;
- (IBAction) menuDeselect:(id)sender;

- (void) closeProject;
- (IBAction) performClose:(id)sender;
- (void) removedDocumentWithPath:(NSString*)path;
- (void) renamedDocumentPathFrom:(NSString*)oldPath to:(NSString*)newPath;

- (BOOL) addCCObject:(CCNode *)obj toParent:(CCNode*)parent atIndex:(int)index;
- (BOOL) addCCObject:(CCNode *)obj toParent:(CCNode*)parent;
- (BOOL) addCCObject:(CCNode*)obj asChild:(BOOL)asChild;
- (CCNode*) addPlugInNodeNamed:(NSString*)name asChild:(BOOL) asChild;
- (void) dropAddPlugInNodeNamed:(NSString*) nodeName at:(CGPoint)pt;
- (void) dropAddPlugInNodeNamed:(NSString *)nodeName parent:(CCNode*)node index:(int)idx;
- (void) deleteNode:(CCNode*)node;
- (IBAction) pasteAsChild:(id)sender;
- (IBAction) menuQuit:(id)sender;

- (int) orientedDeviceTypeForSize:(CGSize)size;
- (IBAction)menuEditCustomPropSettings:(id)sender;
//- (void) updateStateOriginCenteredMenu;
- (IBAction) menuSetStateOriginCentered:(id)sender;
- (void) updateCanvasBorderMenu;
- (IBAction) menuSetCanvasBorder:(id)sender;
- (IBAction) menuZoomIn:(id)sender;
- (IBAction) menuZoomOut:(id)sender;

- (IBAction)menuCreateSmartSpriteSheet:(id)sender;

- (IBAction) pressedToolSelection:(id)sender;
- (IBAction) pressedPanelVisibility:(id)sender;

- (IBAction) menuOpenResourceManager:(id)sender;
- (void) reloadResources;
- (IBAction)menuAddStickyNote:(id)sender;
- (IBAction) menuCleanCacheDirectories:(id)sender;
- (IBAction)menuAbout:(id)sender;
- (IBAction)menuResetSpriteBuilder:(id)sender;

// Undo / Redo
- (void) updateDirtyMark;
- (void) saveUndoState;
- (void) saveUndoStateWillChangeProperty:(NSString*)prop;

- (IBAction) undo:(id)sender;
- (IBAction) redo:(id)sender;
- (IBAction) delete:(id) sender;

- (IBAction) debug:(id)sender;

// Publishing & running
- (void) publisher:(CCBPublisher*)publisher finishedWithWarnings:(CCBWarnings*)warnings;
- (IBAction)runProject:(id)sender;
- (IBAction) menuPublishProjectAndRun:(id)sender;
- (IBAction) menuPublishProjectAndRunInBrowser:(id)sender;

// For warning messages
- (void) modalDialogTitle: (NSString*)title message:(NSString*)msg;

// Modal status messages (progress)
- (void) modalStatusWindowStartWithTitle:(NSString*)title;
- (void) modalStatusWindowFinish;
- (void) modalStatusWindowUpdateStatusText:(NSString*) text;

// Help
- (IBAction)reportBug:(id)sender;
- (IBAction)visitCommunity:(id)sender;
- (IBAction)showHelp:(id)sender;

@end
