#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "ball.h"
#include "project.h"

#include <QProgressDialog>
#include <QGraphicsScene>
#include <QThreadPool>
#include <QFutureWatcher>

#include <map>


class QListWidgetItem;
class QGraphicsEllipseItem;
class QGraphicsPixmapItem;
class QSettings;
class RtiExport;
class HelpDialog;


namespace Ui {
class MainWindow;
}

class RTIScene: public QGraphicsScene {
	Q_OBJECT
public:
	RTIScene(QObject *parent = Q_NULLPTR): QGraphicsScene(parent) {}

signals:
	void borderPointMoved();
	void highlightMoved();
};

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	Project project;
	QString project_filename;

	int currentImage = -1;
	//std::vector<bool> valid; //valid images.

	std::vector<int> progress_jobs;
	QProgressDialog *progress;
	//Progress *progress;
	QFutureWatcher<void> watcher;


	bool init();
	int processImage(int n);

public slots:
	void enableActions();

	void openProject();
	void newProject();
	void saveProject();
	void saveProjectAs();

	void clear(); //clear everything (project, images etc.)
	void openImage(QListWidgetItem *, bool fit = false);
	void next();
	void previous();
	void pointPicked(QPoint p);
	void pointClick(QPoint p);
	void deleteSelected();
	void updateBorderPoints();
	void updateHighlight();

	void imagesContextMenu(QPoint);
	void spheresContextMenu(QPoint);


	void changeSphere(QListWidgetItem *current, QListWidgetItem *previous);
	void setupSpheres();
	void setupSphere(int id, Ball *ball);
	int  addSphere();
	void showSpheres(bool show);

	void removeSphere();
	void showHighlights(size_t n);

	void startMeasure();
	void endMeasure();
	void setupMeasures();

	
	void process();
	void processCurrentSphere();
	void cancelProcess();
	void finishedProcess();

	void saveLPs();
	void loadLP();
	void exportRTI();

	void showHelp();

	void quit();

private:
	Ui::MainWindow *ui;
	QSettings *settings = nullptr;
	RtiExport *rtiexport = nullptr;
	HelpDialog *help = nullptr;
	RTIScene *scene = nullptr;
	QGraphicsPixmapItem *imagePixmap = nullptr;

	enum Measuring { NOPE = 0, FIRST_POINT = 1, SECOND_POINT = 2 };
	Measuring measuring = NOPE;
	Measure *measure = nullptr; //tmporary measure.
	
	bool ignore_scene_changes = false;
	int sphere_to_process = -1;
	QStringList notloaded; //used for looking for highlights and return status.
	QStringList flipped;
	QStringList resolution;
};

#endif // MAINWINDOW_H
