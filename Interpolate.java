import java.util.Arrays;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;

class Interpolate {

    /*
        Class that allows us to make an object to store points
    */
    public static class Point implements Comparable<Point> {
        public final double x, y;
        public Point(double x, double y) {
            this.x = x; this.y = y;
        }
        @Override
        public int compareTo(Point other) {
            return Double.compare(this.x, other.x);
        }
    }

    private Point[] table;

    public Interpolate(Point[] points) {
        this.table = points.clone();
        Arrays.sort(this.table);
    }

    /*
        Loads a CSV file with lines like: 1.0,2.5
    */
    public static Point[] loadCsv(String filename) throws Exception{
        ArrayList<Point> pts = new ArrayList<>();
        BufferedReader br = new BufferedReader(new FileReader(filename));

        String line;
        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;

            String[] parts = line.split(",");
            double x = Double.parseDouble(parts[0].trim());
            double y = Double.parseDouble(parts[1].trim());

            pts.add(new Point(x, y));
        }

        br.close();
        return pts.toArray(new Point[0]);
    }

    private double interpolateHelper(double x0, double y0, double x1, double y1, double x) {
        if (x1 == x0) return y0;
        return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
    }

    public double interpolate(double x) {

        if (x <= table[0].x)
            return interpolateHelper(table[0].x, table[0].y, table[1].x, table[1].y, x);

        if (x >= table[table.length - 1].x)
            return interpolateHelper(
                    table[table.length - 2].x, table[table.length - 2].y,
                    table[table.length - 1].x, table[table.length - 1].y,
                    x
            );

        for (int i = 0; i < table.length - 1; i++) {
            if (x >= table[i].x && x <= table[i + 1].x) {
                return interpolateHelper(table[i].x, table[i].y, table[i + 1].x, table[i + 1].y, x);
            }
        }

        return 0;
    }

    public static void main(String[] args) throws Exception {
        // load from CSV
        Point[] ptsFromCsv = loadCsv("table.csv");
        Interpolate interpolateCsv = new Interpolate(ptsFromCsv);
        System.out.println(interpolateCsv.interpolate(2.5));

        Point[] pts = {
                new Point(0, 0),
                new Point(1, 1),
                new Point(2, 4),
                new Point(4, 16)
        };

        Interpolate interpStatic = new Interpolate(pts);
        System.out.println(interpStatic.interpolate(2.5));
    }
}
