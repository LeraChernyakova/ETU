package lab2;


import java.util.*;

/*
 * Класс, реализующий алгоритм поиска пути в графе
 */
abstract class PathFounder {
    protected final HashMap<Character, PriorityQueue<Edge>> graph = new HashMap<>(); // введённый граф
    protected final char startVertex; // начальная вершина
    protected final char endVertex; // конечная вершина
    protected final String way; // итоговый путь, построенный с помощью жадного алгоритма

    /*
     * Класс направленного ребра
     * без начальной вершины
     */
    protected class Edge implements Comparable<Edge> {
        char to; // конечная вершина
        double weight; // вес ребра

        public Edge(char to, double weight) {
            this.to = to;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge o) {
            return Double.compare(weight, o.weight);
        }
    }

    /*
     * Конструктор
     * считывает сначала начальную и конечную вершины
     * для жадного алгоритма, а далее рёбра графа в формате:
     * <начальная вершина> <конечная вершина> <вес>
     */
    public PathFounder() {
        Scanner scanner = new Scanner(System.in);
        scanner.useLocale(Locale.US);
        startVertex = scanner.next().charAt(0);
        endVertex = scanner.next().charAt(0);
        while (scanner.hasNext()) {
            char buf = scanner.next().charAt(0);
            if (graph.containsKey(buf)) {
                graph.get(buf).add(new Edge(scanner.next().charAt(0), scanner.nextDouble()));
            } else {
                PriorityQueue<Edge> priorityQueue = new PriorityQueue<>();
                priorityQueue.add(new Edge(scanner.next().charAt(0), scanner.nextDouble()));
                graph.put(buf, new PriorityQueue<>(priorityQueue));
            }
        }
        way = runAlgorithm();
    }

    /*
     * Метод нахождения пути в графе
     * возвращает найденный путь
     */
    protected abstract String runAlgorithm();
}

/*
 * Класс, реализующий жадный алгоритм
 */
class GreedyAlgorithm extends PathFounder {
    /*
     * Жадный алгоритма для полей класса
     * Возвращает найденный путь
     */
    @Override
    protected String runAlgorithm() {
        StringBuilder result = new StringBuilder(String.valueOf(startVertex));
        char currentVertex = startVertex;

        while (currentVertex != endVertex) { // если зашли в тупик
            if (graph.get(currentVertex) == null || graph.get(currentVertex).isEmpty()) {
                result.deleteCharAt(result.length() - 1);
                currentVertex = result.charAt(result.length() - 1);
            } else { //если ещё есть куда идти
                currentVertex = graph.get(currentVertex).poll().to;
                result.append(currentVertex);
            }
        }
        return String.valueOf(result);
    }
}

class AStar extends PathFounder {

    /*
     * Класс направленного ребра
     * без начальной вершины
     * содержит функции fx и gx (эвристику)
     * и информацию о предыдущей вершине
     */
    private class EdgeForAStar extends Edge {
        double fx; // длина пути от начальной вершины до текущей
        double gx; //эвристика
        Character prev = null; // предыдущий элемент

        public EdgeForAStar(char to, double weight, double fx, Character prev) {
            super(to, weight);
            this.fx = fx;
            this.gx = Math.abs(to - endVertex);
            this.prev = prev;
        }
    }

    /*
     * Класс с информацией для пройденной вершины:
     */
    private class SettledEdgeInfo {
        Double currentDX; //  длина пути от начальной вершины до текущей
        Character currentPrev; // предыдущий элемент

        public SettledEdgeInfo(Double currentDX, Character currentPrev) {
            this.currentDX = currentDX;
            this.currentPrev = currentPrev;
        }
    }

    /*
     * Компаратор, сравнивающий вершины для алгоритма А*
     */
    private class AStarEdgeComparator implements Comparator<EdgeForAStar> {
        @Override
        public int compare(EdgeForAStar o1, EdgeForAStar o2) {
            return Double.compare(o1.fx + o1.gx, o2.fx + o2.gx);
        }
    }

    /*
     * Алгоритм А*
     * Возвращает найденный путь
     */
    @Override
    protected String runAlgorithm() {
        PriorityQueue<EdgeForAStar> unsettledNodes =
                new PriorityQueue<>(new AStarEdgeComparator()); // очередь непросметренных вершин
        HashMap<Character, SettledEdgeInfo> settledNodes = new HashMap<>(); // просмотренные вершины
        EdgeForAStar currentVertex = new EdgeForAStar(startVertex, 0, 0, null);
        unsettledNodes.add(currentVertex);

        while (currentVertex.to != endVertex) {
            if (graph.get(currentVertex.to) != null) {
                for (Edge edge : graph.get(currentVertex.to)) {
                    //заполнение очереди непройденных вершин
                    if (!settledNodes.containsKey(edge.to)) {
                        unsettledNodes.add(new EdgeForAStar(edge.to, edge.weight, edge.weight + currentVertex.fx, currentVertex.to));
                    } else // обновление пройденной вершиины в случае нахождения более оптимального варианта
                        if (settledNodes.get(edge.to).currentDX > edge.weight + currentVertex.fx) {
                            settledNodes.get(edge.to).currentDX = edge.weight + currentVertex.fx;
                            settledNodes.get(edge.to).currentPrev = currentVertex.to;
                        }
                }
            }
            settledNodes.put(currentVertex.to, new SettledEdgeInfo(currentVertex.fx, currentVertex.prev));
            //нахождение новой непройденной вершины
            while (settledNodes.containsKey(currentVertex.to)) {
                currentVertex = unsettledNodes.poll();
            }
        }
        settledNodes.put(currentVertex.to, new SettledEdgeInfo(currentVertex.fx, currentVertex.prev));
        //нахождение результирующего пути
        StringBuilder result = new StringBuilder();
        while (currentVertex.prev != null) {
            result.append(currentVertex.to);
            currentVertex = new EdgeForAStar(currentVertex.prev,
                    0, 0, settledNodes.get(currentVertex.prev).currentPrev);
        }

        result.append(currentVertex.to);
        return String.valueOf(result.reverse());
    }
}

public class Main {
    public static void main(String[] args) {
        // Для жадного алгоритма
        // PathFounder pathFounder = new GreedyAlgorithm();

        // Для алгоритима А*
        PathFounder pathFounder = new AStar();

        System.out.println(pathFounder.way);
    }
}