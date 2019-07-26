#include <assert.h>
#include <directfb.h>
#include <directfb_strings.h>

#include <unistd.h>    /* for sleep()        */
#include <stdio.h>
#include <string.h>    /* for strcmp()       */

#include "messageFB.h"

/* the super interface */
IDirectFB *dfb = NULL;

/* the primary surface */
IDirectFBSurface *primary = NULL;

/* some test images for blitting */
IDirectFBFont *bench_font = NULL;

int fontHeight = 22;

/* macro for a safe call to DirectFB functions */
#define DFBCHECK(x...)                                                     \
	do {                                                             \
		err = x;                                                    \
		if (err != DFB_OK) {                                        \
			fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
			DirectFBErrorFatal( #x, err );                         \
		}                                                           \
	} while (0)

////////////////////////////////////////////////////////////////////////////////
int stopMessage() {
	if (bench_font) {
		bench_font->Release( bench_font );
		bench_font = NULL;
	}

	if (primary) {
		primary->Release( primary );
		primary = NULL;
	}

	if (dfb) {
		dfb->Release( dfb );
		dfb = NULL;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
int beginMessage(int *argc, char **argv[]) {
	if (primary || dfb) {
		stopMessage();
	}

	DFBResult err;
	DFBSurfaceDescription dsc;

	DFBCHECK(DirectFBInit( argc, argv ));

	DirectFBSetOption ("bg-none", NULL);
	DirectFBSetOption ("no-init-layer", NULL);

	DFBCHECK(DirectFBCreate( &dfb ));
	if (!dfb) {
		return -1;
	}

	err = dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );
	if (err) {
		DirectFBError( "Failed to get exclusive access", err );
	}

	dsc.flags = DSDESC_CAPS;
	dsc.caps = DSCAPS_PRIMARY;

	DFBCHECK(dfb->CreateSurface( dfb, &dsc, &primary ));
	if (!primary) {
		return -1;
	}

	primary->Clear( primary, 0, 0, 0, 0x80 );

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
void clearMessage() {
	assert(primary != NULL);

	primary->Clear( primary, 0, 0, 0, 0x80 );
}

////////////////////////////////////////////////////////////////////////////////
void showMessages(int verticalSpaceDivisor, int nStrings, const char **strings) {
	assert(strings != NULL);
	assert(primary != NULL);
	assert(bench_font != NULL);

	int i;

	clearMessage();

	if (verticalSpaceDivisor < 1) {
		verticalSpaceDivisor = 18;
	}

	int width, height;
	primary->GetSize( primary, &width, &height );

	for (i = 0; i < nStrings; i++) {
		primary->DrawString( primary, strings[i], -1,
				width / 2, height / 2 + i*(height/verticalSpaceDivisor),
				DSTF_CENTER );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void showMessage(const char *message) {
	assert(message != NULL);
	assert(primary != NULL);
	assert(bench_font != NULL);

	showMessages(0, 1, &message);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void setMessageColor(int rgb) {
	assert(primary != NULL);

	primary->SetColor( primary,
			(rgb >> 16) & 0xff,	// red
			(rgb >> 8) & 0xff,	// green
			(rgb) & 0xff,		// blue
			0xff);			// opacity
}

////////////////////////////////////////////////////////////////////////////////
void setMessageFont(const char *font) {
	assert(primary != NULL);
	assert(font != NULL);

	DFBResult err;

	if (bench_font) {
		bench_font->Release( bench_font );
		bench_font = NULL;
	}

	DFBFontDescription desc;
	desc.flags      = (DFBFontDescriptionFlags)(DFDESC_HEIGHT | DFDESC_ATTRIBUTES);
	desc.height     = fontHeight;
	desc.attributes = DFFA_NONE;

	DFBCHECK(dfb->CreateFont( dfb, font, &desc, &bench_font ));
	if (bench_font) {
		primary->SetFont( primary, bench_font );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void setMessageFontHeight(int height) {
	fontHeight = height;
}
