#!/bin/bash

xcodebuild -project ../Builds/MacOSX/Magenta\ Beats.xcodeproj -configuration Release -scheme "Magenta Beats - All"
packagesbuild Magenta\ Beats.pkgproj
dmgcanvas Magenta\ Beats.dmgCanvas Magenta\ Beats.dmg
