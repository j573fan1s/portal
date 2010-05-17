/* $Id: README.txt,v 1.1 2009/09/10 12:47:49 mukhsim Exp $ */
All too often popular sites get flooded with useless comments which would be nice to hide by default from common visitors.
There are several comment moderation methods out there, but after careful examination it becomes apparent that Slashdot comment moderation system is superior to all: http://slashdot.org/moderation.shtml

This module is an attempt to implement Slashdot moderation system in Drupal.

This module does the following:
1. Transforms comment control toolbar (adds threshold field, removes date sorting, simplifies display modes)
2. Overrides default comment_render function from core because comment_render is neither a hook or a themeable function.
3. Adds moderation form to every comment. Moderation form is an exact copy of Slashdot moderation form.

TODO
1. AJAX moderation of comments. 
2. Integration with Karma and Userpoints with the purpose of modpoint distribution.
3. Meta-moderation.
