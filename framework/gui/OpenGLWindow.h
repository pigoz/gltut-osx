#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>

@interface OpenGLWindow : NSWindow
@property (nonatomic, assign, getter=isFullscreen) BOOL fullscreen;
@property (nonatomic, assign) NSRect windowedFrame;
@property (nonatomic, retain) NSString *windowedTitle;

- (IBAction)toggleWindowFullscreen:(id)sender;
- (void)centerOnScreen;
@end
