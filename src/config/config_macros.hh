#pragma once

#define JSON_READ(key, var) if (json.contains(key)) var = json[key]
#define JSON_WRITE(key, var) json[key] = var
