#pragma once

enum KeyNames { C, D, E, F, G, A, H, OctaveDown, OctaveUp, KeyCount };

struct KeyConfig
{
	char bindings[9] = { '1', '2', '3', '4', '5', '6', '7', '9', '0'}; // CDEFGAH, OctaveDown, OctaveUp
};