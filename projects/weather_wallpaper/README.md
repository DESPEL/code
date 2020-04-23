## Detalles
---
Simple script de Python para cambiar el fondo de pantalla según el clima del día.

### Configuración

En `config.py` se pueden establecer:
- Intervalo de cambio del fondo (segundos)
```python3
WALLPAPER_CHANGE_INTERVAL = 600
```
- Ubicación:
```python3
LOCATION = "Tijuana, MX"
```
- API Key de OWM
```python3
APIKEY = "API-KEY"
```
- Resultados máximos (imágenes diferentes para un mismo clima)
```python3
MAX_RESULTS = 20
```

### Uso
Es necesario instalar los módulos
- pyowm

Ejecución:
- Ejecutar `main.py`
