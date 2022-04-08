#!/bin/bash

dbus-send --session --print-reply --dest=sdbus.example.api /org/sdbus/examples consent.dbus.api.ConsentManager.concatenate string:'Hallo' string:'Welt'
