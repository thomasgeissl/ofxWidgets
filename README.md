# ofxWidgets (aka ofxYaga - yet another gui addon)
## Description
It seems like every oF developer has written a gui addon, this is mine. This is more of an experiment than anything serious, not sure how much time i will have in the future to develop this addon. 
Contributions are very welcome.

Widget based gui addon. Each widget draws into its own FBO and only gets redrawn if flagged as dirty.

Current state: mostly broken

The addon includes the following widgets:
* gui - container for all other widgets, registers automatically to ofEvents
* widget - base widget
* label
* slider
    * int
    * float
    * double
* button
* toggle
* dropDown
    * int
    * float
    * double
    * string

These widgets hold internaly ofParameter objects. You can pass in your own parameters.

In order to layout your gui, you can use one of the following layouts:
* boxLayout
    * hBox
    * vBox
* tabLayout
* gridLayout

## License
This project is released under MIT license, please note that dependencies might be released differently.

Copyright (c) 2019 Thomas Geissl

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.