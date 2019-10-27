struct rectangular {
    float x;
    float y;
}

struct polar {
    float m;
    float a;
}

struct Vector2D {
    rectangular r;
    polar p;
    bool esPolar;

    Vector2D(float x, float y, bool pol) {
        esPolar = pol;
        if (pol) {
            p.m = x;
            p.a = y;
        } else {
            r.x = x;
            r.y = y;
        }
    }

    void convertir() {
        if (espolar) {
            // nuevo codigo de polar a
            // rectangular
        } else {
            // lo que tienes para rectangular
            // a polar
        }
    }
};

int main () {
    float x, y;
    cin >> x;
    cin >> y;
    Vector2D rect(x, y, false);
}