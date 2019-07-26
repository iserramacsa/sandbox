#ifndef MessageFB_h__
#define MessageFB_h__

#ifdef __cplusplus
extern "C" {
#endif
	int beginMessage(int *argc, char **argv[]);
	int stopMessage();

	void setMessageColor(int rgb);
	void setMessageFont(const char *font);
	void setMessageFontHeight(int height);

	void clearMessage();
	void showMessage(const char *string);
	void showMessages(int verticalSpaceDivisor, int nStrings, const char **strings);
#ifdef __cplusplus
}
#endif

#endif
