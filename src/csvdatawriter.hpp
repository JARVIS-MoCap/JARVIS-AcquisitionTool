#ifndef CSVDATAWRITER_H
#define CSVDATAWRITER_H

#include "globals.hpp"
#include <QTextStream>

class CSVDataWriter : public QObject {
    Q_OBJECT

  public:
    CSVDataWriter(QString file_path, QStringList header,
                  QString septerator = ";") {

        this->seperator = septerator;
        this->file_path = file_path;

        this->file = new QFile(file_path, this);
        if (this->file->open(QIODevice::ReadWrite)) {
            this->file_stream = new QTextStream(this->file);
            this->open = true;
        }

        this->headerLen = header.length();
        write(header);
    }

    ~CSVDataWriter() {
        if (this->open) {
            close();
        }
        delete file;
        delete file_stream;
    }

  public slots:
    void close() {
        this->open = false;
        this->file_stream->flush();
        this->file->close();
    }

    void write(QStringList args) {
        if (!this->open) {
            qCritical() << "CSVWriter not open: " << this->file_path;
            return;
        }
        if (args.length() != this->headerLen) {
            qCritical() << "Arguments don't fit header, expected: "
                        << this->headerLen << " got: " << args.length()
                        << " File: " << this->file_path;
            return;
        }
        *file_stream << args.join(seperator) << endl;
    }
    void write(QVariantList args) {
        QStringList stringArgs;
        foreach (const QVariant item, args) {
            stringArgs.append(item.toString());
        }
        write(stringArgs);
    }

  signals:
  private:
    bool open = false;
    int headerLen = 0;
    int rowCurser = 0;
    QString seperator;
    QString file_path;
    QFile *file;
    QTextStream *file_stream;
};

#endif
