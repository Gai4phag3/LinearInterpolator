public class Interpolate {
    public static double interpolate(double firstX, double firstY, double secondX, double secondY, double interpolatedX) {
        if (firstX == secondX) {
            return 0;
        }
        return firstY + (secondY - firstY) * (interpolatedX - firstX) / (secondX - firstX);
    }

    public static void main(String[] args) {
        System.out.println("Interpolated Y: " + interpolate(0, 0, 1, 1, 0.5)); 
    }
}
