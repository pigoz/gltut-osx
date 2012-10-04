//
//  main.m
//  A Nibless OpenGL Cocoa Application
//  (inspired by http://cocoawithlove.com/2010/09/minimalist-cocoa-programming.html)
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/QuartzCore.h>

#import "gui/OpenGLWindow.h"
#import "gui/OpenGLView.h"

static float _time = 0;

float getElapsedTime()
{
    return _time;
}

void setElapsedTime(float time)
{
    _time = time;
}

static NSString *appName(void)
{
    return [[NSProcessInfo processInfo] processName];
}

static void createMenu(void)
{
    id menubar = [[NSMenu new] autorelease];
    id appMenuItem = [[NSMenuItem new] autorelease];
    [menubar addItem:appMenuItem];
    [NSApp setMainMenu:menubar];
    id appMenu = [[NSMenu new] autorelease];
    id quitTitle = [@"Quit " stringByAppendingString:appName()];
    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                  action:@selector(terminate:)
                                           keyEquivalent:@"q"] autorelease];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
}

static NSRect windowSize(void) {
    return NSMakeRect(0, 0, 600, 600);
}

static void runApplication(void)
{
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    createMenu();
    id window = [[[OpenGLWindow alloc] initWithContentRect:windowSize()
                                             styleMask:NSTitledWindowMask
                                               backing:NSBackingStoreBuffered
                                                 defer:NO] autorelease];
    [window centerOnScreen];
    [window setTitle:appName()];
    [window awakeFromNib];

    id view = [[[OpenGLView alloc] init] autorelease];
    [window setContentView:view];
    [view awakeFromNib];

    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
}

int main(int argc, char *argv[])
{
    @autoreleasepool {
        runApplication();
    }
    return 0;
}
