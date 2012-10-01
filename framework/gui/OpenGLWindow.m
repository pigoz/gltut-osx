#import "OpenGLWindow.h"

#define _HIDDEN_PRESENTATION  NSApplicationPresentationHideDock|\
                              NSApplicationPresentationHideMenuBar
#define _DEFAULT_PRESENTATION NSApplicationPresentationDefault

#define _BORDERLESS_MASK      NSBorderlessWindowMask
#define _DEFAULT_MASK         NSTitledWindowMask|NSClosableWindowMask|\
                              NSMiniaturizableWindowMask|NSResizableWindowMask

@implementation OpenGLWindow

@synthesize fullscreen    = _fullscreen;
@synthesize windowedFrame = _windowed_frame;
@synthesize windowedTitle = _windowed_title;

-(void)awakeFromNib
{
    [self initAttributes];
    [self applyAttributesBasedOnState];
}

- (void)initAttributes
{
    self.fullscreen = NO;
    self.windowedFrame = [self frame];
    self.windowedTitle = [self title];
}

- (void)applyAttributes:(BOOL)state
{   if (state) {
        [NSApp setPresentationOptions: _HIDDEN_PRESENTATION];
        [self setHasShadow: NO];
        [self setStyleMask: _BORDERLESS_MASK];
        [self setMovableByWindowBackground: NO];
        self.windowedFrame = [self frame];
        [self setFrame:[[self screen] frame] display:YES];
    } else {
        [NSApp setPresentationOptions: _DEFAULT_PRESENTATION];
        [self setHasShadow: YES];
        [self setStyleMask: _DEFAULT_MASK];
        [self setMovableByWindowBackground: YES];
        [self setFrame:self.windowedFrame display:YES];
        [self setTitle:self.windowedTitle];
    }
}

- (void)centerOnScreen
{
    NSRect winFrame = [self frame];
    NSRect screenFrame = [[self screen] frame];
    CGFloat x = NSWidth(screenFrame) /2 - NSWidth(winFrame) /2;
    CGFloat y = NSHeight(screenFrame)/2 - NSHeight(winFrame)/2;
    [self setFrame:NSMakeRect(x, y, NSWidth(winFrame), NSHeight(winFrame))
           display:YES];
}

- (void)applyAttributesBasedOnState
{
    [self applyAttributes:self.isFullscreen];
}

- (IBAction)toggleWindowFullscreen:(id)sender
{
    self.fullscreen = !self.isFullscreen;
    [self applyAttributesBasedOnState];
}

- (void)dealloc
{
    [self applyAttributes:NO];
    [super dealloc];
}
@end
